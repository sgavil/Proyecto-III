#include "GameState.h"



GameState::GameState()
{
}

void GameState::start()
{
}

GameState::~GameState()
{
	for (Component* c : scene) delete c;
}


void GameState::update(unsigned int time)
{
	for (Component* c : scene) c->update(time); 
}

void GameState::render(unsigned int time)
{
	for (Component* c : scene) c->render(time);
}

void GameState::handleInput()
{
	for (Component* c : scene) c->handleEvent();
}