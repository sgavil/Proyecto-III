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
}

void MainMenuState::update(unsigned int time)
{
	GameState::update(time);
}

void MainMenuState::render(unsigned int time)
{
	GameState::render(time);
}

bool MainMenuState::handleInput(unsigned int time)
{
	return GameState::handleInput(time);
}