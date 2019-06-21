#include "Game.h"

//NUESTRO
#include <PARKEngine/PARKManagers.h>
#include <PARKEngine/PARKFoundation.h>

#include "SDL.h"


Game::Game(std::string basicConfig):exit(false)
{
	//Inicializamos singletons
	OgreManager::initInstance(basicConfig);
	//ResourceManager::initInstance();// -> se hace en el OgreManager
	InputManager::initInstance();
	HUDManager::initInstance();
	AudioManager::initInstance();
	SceneManager::initInstance(&exit);
	PhysicsManager::initInstance();
	CallbackManager::initInstance();

	//Cogemos las instancias en las variables
	ogreManager_ = OgreManager::instance();
	inputManager_ = InputManager::instance();
	hudManager_ = HUDManager::instance();
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
	if (hudManager_ != nullptr)
		delete hudManager_;
	if (inputManager_ != nullptr)
		delete inputManager_;
	if (ogreManager_ != nullptr)
		delete ogreManager_;
}

void Game::start()
{
	sceneManager_->changeState("StateMainMenu");

	audioManager_->READ_JSON_SOUNDS("AudioSource.json");
	//AudioManager::instance()->PLAY_2D_SOUND("cochecitos");
	audioManager_->PLAY_SONG("Menu");
	inputManager_->addMappingValues("Input.json");
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
		inputManager_->capture();
		sceneManager_->currentState()->handleInput(deltaTime);
		ogreManager_->render(deltaTime);

		//Actualiza el deltaTime
		deltaTime = SDL_GetTicks() - actualTime;
		actualTime = SDL_GetTicks();	
	}
}
