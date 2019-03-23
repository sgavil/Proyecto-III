#include "Game.h"
#include <Arquitectura/Components.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "BureaucracyManager.h"
//#include <CEGUI/CEGUI.h>
//#include <CEGUI/RendererModules/Ogre/Renderer.h>


Game::Game(std::string basicConfig):exit(false)
{
	ogreSyst_ = OgreSystem::instance(basicConfig);
	GestorRecursos::instance()->ceguiInit();
	audioSrc_ = AudioSource::instance();
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

	ScnMng_->addState("StateTest");
	ScnMng_->changeState("StateTest");

	//--------------------------TEST DE REPRODUCCION DE SONIDO--------------------------//

	AudioSource::instance()->READ_JSON_SOUNDS("AudioSource.json");
	AudioSource::instance()->PLAY_2D_SOUND("cochecitos");

	////-----------------------------------------------------------------------------------//

	////2.Cabeza de Simbad-> tiene un componente para renderizarlo (con su nodo, posición..) y un rigidbody que depende de este
	Transform* simbadTransform = new Transform(Vector3( 0, 1500, 1000 ), Quaternion::IDENTITY, Vector3(3, 3, 3));
	MeshRenderer* simbadRenderer = new MeshRenderer("ogrehead.mesh");
	Rigidbody* simbadRigidbody = new Rigidbody(simbadTransform, Shape::BoxShape, 10);
	Entity* simbad = new Entity(std::vector<Component*>{simbadTransform, simbadRenderer, simbadRigidbody}, "Simbad");
	ScnMng_->currentState()->addEntity(simbad);

	//////3.Suelo y techo
	Transform* florTransform = new Transform(Vector3(0, 1400, 1000), Quaternion::IDENTITY, Vector3(5, 0.5, 5));
	MeshRenderer* floorRenderer = new MeshRenderer("ogrehead.mesh");
	floorRigidbody = new Rigidbody(florTransform, Shape::BoxShape, 0); //Estático
	Entity* floor = new Entity(std::vector<Component*>{ florTransform, floorRenderer, floorRigidbody}, "Floor");
	ScnMng_->currentState()->addEntity(floor);

	Transform* ceilTransform = new Transform(Vector3(0, 1700, 1000), Quaternion::IDENTITY, Vector3(5, 0.5, 5));
	MeshRenderer* ceilRenderer = new MeshRenderer("ogrehead.mesh");
	Rigidbody* ceilRigidbody = new Rigidbody(ceilTransform, Shape::BoxShape, 0); //Estático
	Entity* ceil = new Entity(std::vector<Component*>{ ceilTransform, ceilRenderer, ceilRigidbody}, "Ceil");
	ScnMng_->currentState()->addEntity(ceil);

	//////4.Terreno
	Terrain* terrainComp = new Terrain("Maps.json");
	Entity* terrain = new Entity(std::vector<Component*>{terrainComp}, "Terrain");
	ScnMng_->currentState()->addEntity(terrain);

	run();
}

void Game::run()
{
	//Start
	ScnMng_->currentState()->start();

	//Tiempo entre frames y tiempo total transcurrido
	unsigned int deltaTime, actualTime;
	actualTime = deltaTime = SDL_GetTicks();
	//Bucle principal
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
