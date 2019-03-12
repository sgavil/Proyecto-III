#include "Game.h"
#include <Arquitectura/Components.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

Game::Game(std::string basicConfig):exit(false)
{
#if _DEBUG
	root = new Ogre::Root("plugins_d.cfg");
#else 	
	root = new Ogre::Root("plugins.cfg");
#endif

	Ogreinit_ = new initOgreApplication(root, basicConfig);
	audioSrc_ = new AudioSource();
	
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
	physicSystem::instance()->clenanupPhysics();
	delete physicSystem::instance();
	CEGUI::System::destroy();
	//CEGUI::OgreRenderer::destroy(static_cast<CEGUI::OgreRenderer&>()//*d_renderer));
}

void Game::start()
{
	PlayState* playstate = new PlayState(); 
	ScnMng_->addState(PLAY, playstate);
	ScnMng_->changeState(PLAY);

	physicSystem::instance()->initPhysics();

	//--------------------------TEST DE COMPONENTE EN UNA ESCENA--------------------------//
	
	//1.Cámara
	CameraComponent*  camComp = new CameraComponent(Ogreinit_->getSceneManager(), Ogreinit_->getWindow());
	Entity* camera = new Entity(std::vector<Component*>{camComp}, "Camera");
	ScnMng_->currentState()->addEntity(camera);

	//-----------------------------------------------------------------------------------//
	//--------------------------TEST DE REPRODUCCION DE SONIDO--------------------------//

	audioSrc_->ADD_SOUND("Assets\\Audio\\Cochecitos.mp3");
	audioSrc_->PLAY_SOUND("Assets\\Audio\\Cochecitos.mp3");

	//-----------------------------------------------------------------------------------//

	

	//2.Cabeza de Simbad-> tiene un componente para renderizarlo (con su nodo, posición..) y un rigidbody que depende de este
	RenderComponent* simbadRenderComp = new RenderComponent(Ogreinit_->getSceneManager(), "ogrehead.mesh", Ogre::Vector3{ 0, 2000, 1500 });
	RigidbodyComponent* simbadRigidComp = new RigidbodyComponent(simbadRenderComp->getNode(), Shape::BoxShape, 1, 10);
	Entity* simbad = new Entity(std::vector<Component*>{simbadRenderComp, simbadRigidComp}, "Simbad");
	ScnMng_->currentState()->addEntity(simbad);

	//3.Plano invisible
	RigidbodyComponent* floorRigidComp = new RigidbodyComponent(Ogre::Vector3(1683, 1000, 2116), Shape::PlaneShape, 100, 0);
	Entity* floor = new Entity(std::vector<Component*>{floorRigidComp}, "Floor");
	ScnMng_->currentState()->addEntity(floor);

	//4.Terreno
	TerrainComponent* terrainComp = new TerrainComponent(Ogreinit_->getSceneManager(), Ogreinit_->getLight(), "Maps.json");
	Entity* terrain = new Entity(std::vector<Component*>{terrainComp}, "Terrain");
	ScnMng_->currentState()->addEntity(terrain);

	run();
}

void Game::run()
{
	//Tiempo entre frames y tiempo total transcurrido
	unsigned int deltaTime, actualTime;
	actualTime = deltaTime = SDL_GetTicks();

	while (!exit)
	{
		//Llama al update, handleInput y render de la escena activa
		ScnMng_->currentState()->update(deltaTime);
		ScnMng_->currentState()->handleInput(deltaTime);
		root->renderOneFrame((Ogre::Real)deltaTime / 1000);

		//Actualiza el deltaTime
		deltaTime = SDL_GetTicks() - actualTime;
		actualTime = SDL_GetTicks();
	}
}
