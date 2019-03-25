#include "GameState.h"
#include <Arquitectura/physicSystem.h>
#include <Arquitectura/EntityFactory.h>
#include <Arquitectura/InputManager.h>

GameState::GameState(std::string stateID)
{
	addEntities(EntityFactory::Instance()->createEntities(stateID));
}


GameState::~GameState()
{
	auto it = scene.begin();
	while (it != scene.end())
	{
		Entity* e = (*it)->getEntity();
		Entity* aux = (*it)->getEntity();

		while (it != scene.end() && &e != nullptr && e == aux) {
			delete (*it);
			++it;
			if(it != scene.end())
				aux = (*it)->getEntity();
		}
		delete e;
		e = nullptr;
	}
	
}

void GameState::start()
{
	for (Component* c : scene)
		if (c->isActive())
			c->start();
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

bool GameState::handleInput(unsigned int time)
{
	bool handled = false;

	//while (SDL_PollEvent(&event))
	//{
	//	if (event.type == SDL_QUIT)
	//	{
	//		return true;
	//	}
	//	// LLama al handleInput de todos los componentes 
	//	else 
	//	{
	//		std::list<Component*>::iterator it = scene.begin();
	//		while (it != scene.end() && !handled)
	//		{
	//			if ((*it)->isActive())
	//				handled = (*it)->handleEvent(&event, time);
	//			it++;
	//		}
	//	}
	//}
	
	Event e = InputManager::instance()->CheckInput();
	std::list<Component*>::iterator it = scene.begin();
	if (e.keyboard_->isKeyDown(OIS::KC_ESCAPE)) return true;
	while (it != scene.end() && !handled)
		{
			if ((*it)->isActive())
			handled = (*it)->handleEvent(e, time);
			it++;
		}
			return false;
}

void GameState::addEntity(Entity* e)
{
	for (Component* c : e->getComponents()) 
		scene.push_back(c);
}

void GameState::addEntities(std::vector<Entity*> ent)
{
	for (Entity* e : ent)
		addEntity(e);
}

bool GameState::removeEntity(std::string name)
{
	bool found = false;

	std::list<Component*>::iterator it = scene.begin();
	// Eliminamos todos los componentes con esa entidad
	while (it != scene.end())
	{
		if ((*it)->getEntity()->getName() == name)
		{
			it = scene.erase(it);
			found = true;
		}
			
		else
			it++;
	}
	return found;
}

Entity* GameState::getEntity(std::string name)
{
	Entity* e = nullptr;
	std::list<Component*>::iterator it = scene.begin();

	// Buscamos al primer componente que tenga esa entidad
	while (it != scene.end() && e == nullptr)
	{
		if ((*it)->getEntity()->getName() == name)
			e = (*it)->getEntity();
		it++;
	}

	return e;
}