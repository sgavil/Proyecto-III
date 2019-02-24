#include "SceneManager.h"


MainMenuState::MainMenuState() : GameState()
{
	start();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::start()
{
	PlayState* play = new PlayState();
	SceneManager::instance()->addState(PLAY, play);
}

void MainMenuState::update(unsigned int time)
{
	GameState::update(time);
}

void MainMenuState::render(unsigned int time)
{
	GameState::render(time);
}

void MainMenuState::handleInput()
{
	GameState::handleInput();
}