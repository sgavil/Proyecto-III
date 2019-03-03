#include "SceneManager.h"


PlayState::PlayState() : GameState()
{
	start();
}

PlayState::~PlayState()
{
}


void PlayState::start()
{
	
}


void PlayState::update(unsigned int time)
{
	GameState::update(time);
}

void PlayState::render(unsigned int time)
{
	GameState::render(time);
}

void PlayState::handleInput()
{
	GameState::handleInput();
}