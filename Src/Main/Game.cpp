#include "Game.h"

//NUESTRO
#include <PARKEngine/PARKManagers.h>
#include <PARKEngine/PARKFoundation.h>

#include "SDL.h"


Game::Game(std::string basicConfig):exit(false)
{
	ogreManager_ = OgreManager::instance(basicConfig);

	inputManager_ = InputManager::getSingletonPtr();
	inputManager_->initialise();

	hudManager_ = HUDManager::instance();
	hudManager_->init();

	audioManager_ = AudioManager::instance();

	sceneManager_ = SceneManager::instance();
	sceneManager_->setExit(&exit);

	physicsManager_ = PhysicsManager::instance();
	physicsManager_->init();
}

Game::~Game()
{
	if (physicsManager_ != nullptr)
		delete physicsManager_;
	if (sceneManager_ != nullptr)
		delete sceneManager_;
	if (audioManager_ != nullptr)
		delete audioManager_;
	if (inputManager_ != nullptr)
		delete inputManager_;
	if (ogreManager_ != nullptr)
		delete ogreManager_;
}

void Game::start()
{
	sceneManager_->changeState("StateMainMenu");

	AudioManager::instance()->READ_JSON_SOUNDS("AudioSource.json");
	//AudioManager::instance()->PLAY_2D_SOUND("cochecitos");
	AudioManager::instance()->PLAY_SONG("Menu");
	InputManager::getSingletonPtr()->addMappingValues("Input.json");
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
		sceneManager_->currentState()->handleInput(deltaTime);
		ogreManager_->render(deltaTime);

		//Actualiza el deltaTime
		deltaTime = SDL_GetTicks() - actualTime;
		actualTime = SDL_GetTicks();	
	}
}
