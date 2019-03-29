#include "Game.h"

//NUESTRO
#include <PARKEngine/PhysicsManager.h>
#include <PARKEngine/AudioManager.h>
#include <PARKEngine/OgreManager.h>
#include <PARKEngine/InputManager.h>
#include <PARKEngine/Entity.h>
#include <PARKEngine/SceneManager.h> 
#include "BureaucracyManager.h"
#include <PARKEngine/EntityFactory.h>

//CEGUI/OIS
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "SDL.h"


Game::Game(std::string basicConfig):exit(false)
{
	
	ogreSyst_ = OgreManager::instance(basicConfig);
	InputManager::getSingletonPtr()->initialise(OgreManager::instance()->getWindow());
	ResourceManager::instance()->ceguiInit();
	audioSrc_ = AudioManager::instance();
	ScnMng_ = SceneManager::instance();
	physSyst_ = PhysicsManager::instance();
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

	AudioManager::instance()->READ_JSON_SOUNDS("AudioSource.json");
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