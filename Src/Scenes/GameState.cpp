#include "GameState.h"

GameState::GameState()
{
}

GameState::~GameState()
{
	for (Entity* e : scene) delete e;
}

void GameState::update()
{
	for (Entity* e : scene); //e->update();
}

void GameState::render()
{
	for (Entity* e : scene);//e->render();
}

void GameState::handleInput()
{
	for (Entity* e : scene); //e->handleInput();
}