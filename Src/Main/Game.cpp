#include "Game.h"

//NUESTRO
#include <PARKEngine/PARKManagers.h>
#include <PARKEngine/EntityFactory.h>


//CEGUI/OIS
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "SDL.h"


Game::Game(std::string basicConfig):exit(false)
{
	ogreManager_ = OgreManager::instance(basicConfig);
	InputManager::getSingletonPtr()->initialise(OgreManager::instance()->getWindow());
	ResourceManager::instance()->ceguiInit();
	audioManager_ = AudioManager::instance();
	sceneManager_ = SceneManager::instance();
	physicsManager_ = PhysicsManager::instance();
}

Game::~Game()
{
	if (physicsManager_ != nullptr)
		delete physicsManager_;
	if (sceneManager_ != nullptr)
		delete sceneManager_;
	if (audioManager_ != nullptr)
		delete audioManager_;

	if (ogreManager_ != nullptr)
		delete ogreManager_;
	//CEGUI::System::destroy();
	//CEGUI::OgreRenderer::destroy(static_cast<CEGUI::OgreRenderer&>()//*d_renderer));
}

void Game::start()
{
	sceneManager_->addState("StateTest");
	sceneManager_->changeState("StateTest");

	AudioManager::instance()->READ_JSON_SOUNDS("AudioSource.json");
	AudioManager::instance()->PLAY_2D_SOUND("cochecitos");
	InputManager::getSingletonPtr()->addMappingValues("Input.json");
	//Start
	sceneManager_->currentState()->start();

	// TEST DE LOS BLUEPRINTS CON PARÁMETROS (SALE BIEN)
	//EntityFactory::Instance()->createEntityFromBlueprint("NPC");
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
		sceneManager_->currentState()->update(deltaTime);
		InputManager::getSingletonPtr()->capture();
		exit = sceneManager_->currentState()->handleInput(deltaTime);
		ogreManager_->render(deltaTime);

		//Actualiza el deltaTime
		deltaTime = SDL_GetTicks() - actualTime;
		actualTime = SDL_GetTicks();	
	}
}