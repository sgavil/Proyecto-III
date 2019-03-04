

#include "Game.h"
#include <Arquitectura/Components.h>

Game::Game(std::string basicConfig)
{
#if _DEBUG
	root = new Ogre::Root("plugins_d.cfg");
#else 	
	root = new Ogre::Root("plugins.cfg");
#endif

	Ogreinit_ = new initOgreApplication(root, basicConfig);

	//Inicialización de ventana de SDL que se una a la de Ogre
	SDL_Init(SDL_INIT_EVERYTHING);
	hWnd = 0;
	Ogreinit_->getWindow()->getCustomAttribute("WINDOW", &hWnd);
	SDL_CreateWindowFrom((void*)hWnd);

	ScnMng_ = SceneManager::instance();

	//Físicas
	pSystem_ = physicSystem::instance();


}

Game::~Game()
{
	delete ScnMng_;
	delete root;
	pSystem_->clenaupPhysics();
	delete pSystem_;
}

void Game::start()
{
	PlayState* playstate = new PlayState();
	ScnMng_->addState(PLAY, playstate);
	ScnMng_->changeState(PLAY);

	//--------------------------TEST DE COMPONENTE EN UNA ESCENA--------------------------//
	Entity* camera = new Entity();
	CameraComponent*  camComp = new CameraComponent(Ogreinit_->getSceneManager(), Ogreinit_->getWindow());
	camera->addComponent(camComp);

	ScnMng_->currentState()->addComponent(camComp);
	//-----------------------------------------------------------------------------------//

	//FISICAS
	Ogre::Vector3 cameraPos = Ogreinit_->getSceneManager()->getSceneNode("camNode")->getPosition();
	Ogreinit_->getSceneManager()->getSceneNode("simbadNode")->setPosition(cameraPos - Ogre::Vector3(10, 125, 0));
	pSystem_->initPhysics();

	update(SDL_GetTicks());
}

void Game::update(int time)
{
	while (true)
	{
		ScnMng_->currentState()->update(time);
		pSystem_->stepSimulation(); //FÍSICAS
		root->renderOneFrame();
	}
}
