#include "Game.h"
#include <Arquitectura/Components.h>

Game::Game(std::string basicConfig):exit(false)
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

}

Game::~Game()
{
	delete ScnMng_;
	delete root;
	physicSystem::instance()->clenaupPhysics();
	delete physicSystem::instance();
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
	physicSystem::instance()->initPhysics();

	Ogre::SceneNode* simbadNode = Ogreinit_->getSceneManager()->getSceneNode("simbadNode");
	Ogre::Vector3 cameraPos = Ogreinit_->getSceneManager()->getSceneNode("camNode")->getPosition();
	simbadNode->setPosition(cameraPos - Ogre::Vector3(10, 125, 0));

	//Simbad
	RigidbodyComponent* ogreRigidComp = new RigidbodyComponent(simbadNode, Shape::BoxShape, 1, 10);
	ScnMng_->currentState()->addComponent(ogreRigidComp);

	//Plano invisible
	RigidbodyComponent* floorRigidComp = new RigidbodyComponent(Ogre::Vector3(1683, 1000, 2116), Shape::PlaneShape, 100, 0);
	ScnMng_->currentState()->addComponent(floorRigidComp);

	//TERRENO
	Entity* terrain = new Entity();
	TerrainComponent* terrainComp = new TerrainComponent(Ogreinit_->getSceneManager(), Ogreinit_->getLight(), "Maps.json");
	terrain->addComponent(terrainComp);

	run();
}

void Game::run()
{
	int time = SDL_GetTicks();
	while (!exit)
	{
		ScnMng_->currentState()->update(time);
		ScnMng_->currentState()->handleInput();
		physicSystem::instance()->stepSimulation(); //FÍSICA
		root->renderOneFrame();
	}
}
