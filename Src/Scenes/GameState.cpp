#include "GameState.h"



GameState::GameState()
{
}

void GameState::start()
{
}

GameState::~GameState()
{
	for (Component* c : scene) 
		delete c;
}


void GameState::update(unsigned int time)
{
	for (Component* c : scene)
		if(c->isActive())
			c->update(time); 
}

void GameState::render(unsigned int time)
{
	for (Component* c : scene)
		if (c->isActive())
			c->render(time);
}

void GameState::handleInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			//EXIT = true;
		}
		else 
		{
			for (Component* c : scene)
				if (c->isActive())
					c->handleEvent(&event);
		}
	}
	
}