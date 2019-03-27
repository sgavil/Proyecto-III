#include "Game.h"

//NUESTRO
#include <Arquitectura/physicSystem.h>
#include <Arquitectura/AudioSource.h>
#include <Arquitectura/OgreSystem.h>
#include <Arquitectura/InputManager.h>
#include <Arquitectura/Entity.h>
#include <Scenes/SceneManager.h> 
#include "BureaucracyManager.h"
#include <Arquitectura/EntityFactory.h>

//CEGUI/OIS
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "SDL.h"


Game::Game(std::string basicConfig):exit(false)
{
	
	ogreSyst_ = OgreSystem::instance(basicConfig);
	InputManager::getSingletonPtr()->initialise(OgreSystem::instance()->getWindow());
	ResourceManager::instance()->ceguiInit();
	audioSrc_ = AudioSource::instance();
	ScnMng_ = SceneManager::instance();
	physSyst_ = PhysicSystem::instance();
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
	//AudioSource::instance()->PLAY_2D_SOUND("cochecitos");

	//Start
	ScnMng_->currentState()->start();


	// TEST DE LOS BLUEPRINTS CON PARÁMETROS (SALE BIEN)
	EntityFactory::Instance()->createEntityFromBlueprint("NPC");
}

void Game::run()
{
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