#include "GameState.h"
#include <iostream>


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
	physicSystem::instance()->stepSimulation(time); //FÍSICA

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

void GameState::handleInput(unsigned int time)
{
	bool handled = false;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			//EXIT = true;
		}
		//LLama al handleInput de todos los componentes 
		else 
		{
			std::vector<Component*>::iterator it = scene.begin();
			while (it != scene.end() && !handled)
			{
				if ((*it)->isActive())
					handled = (*it)->handleEvent(&event, time);
				it++;
			}
		}
	}
}