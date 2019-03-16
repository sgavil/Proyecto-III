#include "Game.h"
#include <Arquitectura/Components.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

//#include <CEGUI/CEGUI.h>
//#include <CEGUI/RendererModules/Ogre/Renderer.h>


Game::Game(std::string basicConfig):exit(false)
{
	ogreSyst_ = OgreSystem::instance(basicConfig);
	audioSrc_ = new AudioSource();
	ScnMng_ = SceneManager::instance();
	physSyst_ = physicSystem::instance();
}

Game::~Game()
{
	if (physSyst_ != nullptr)
		delete physSyst_;
	if (audioSrc_ != nullptr)
		delete audioSrc_;
	if (ScnMng_ != nullptr)
		delete ScnMng_;
	if (ogreSyst_ != nullptr)
		delete ogreSyst_;
	//CEGUI::System::destroy();
	//CEGUI::OgreRenderer::destroy(static_cast<CEGUI::OgreRenderer&>()//*d_renderer));
}

void Game::start()
{

	ScnMng_->addState("TestState");
	ScnMng_->changeState("TestState");
	//PlayState* playstate = new PlayState(); 
	//ScnMng_->addState(PLAY, playstate);
	//ScnMng_->changeState(PLAY);

	physicSystem::instance()->initPhysics();

	////--------------------------TEST DE COMPONENTE EN UNA ESCENA--------------------------//
	//
	////1.Cámara

	/*CameraComponent*  camComp = new CameraComponent();
	Entity* camera = new Entity(std::vector<Component*>{camComp}, "Camera");
	ScnMng_->currentState()->addEntity(camera);*/

	//-----------------------------------------------------------------------------------//
	//--------------------------TEST DE REPRODUCCION DE SONIDO--------------------------//

	audioSrc_->ADD_2D_SOUND("Assets\\Audio\\Cochecitos.mp3");
	audioSrc_->PLAY_2D_SOUND("Assets\\Audio\\Cochecitos.mp3");

	//-----------------------------------------------------------------------------------//

	//2.Cabeza de Simbad-> tiene un componente para renderizarlo (con su nodo, posición..) y un rigidbody que depende de este
	Transform* simbadTransform = new Transform(Ogre::Vector3{ 0, 1500, 1000 });
	MeshRenderer* simbadMeshRenderer = new MeshRenderer("ogrehead.mesh");
	Rigidbody* simbadRigidbody = new Rigidbody(Shape::BoxShape, 1, 10);
	Entity* simbad = new Entity(std::vector<Component*>{simbadTransform, simbadMeshRenderer, simbadRigidbody}, "Simbad");
	ScnMng_->currentState()->addEntity(simbad);

	////3.Plano invisible
	Transform* floorTransform = new Transform(Ogre::Vector3(1683, 1000, 2116));
	floorRigidbody = new Rigidbody(Shape::PlaneShape, 100, 0);
	Entity* floor = new Entity(std::vector<Component*>{floorTransform, floorRigidbody}, "Floor");
	ScnMng_->currentState()->addEntity(floor);

	////4.Terreno
	TerrainComponent* terrainComp = new TerrainComponent("Maps.json");
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
		exit = ScnMng_->currentState()->handleInput(deltaTime);
		ogreSyst_->render(deltaTime);

		//Actualiza el deltaTime
		deltaTime = SDL_GetTicks() - actualTime;
		actualTime = SDL_GetTicks();
	}
}
