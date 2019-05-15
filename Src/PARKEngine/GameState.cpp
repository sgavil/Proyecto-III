#include "GameState.h"
#include "PARKManagers.h"
#include "EntityFactory.h"
#include "Entity.h"
#include "Component.h"
#include "Button.h"
#include "OgreIncludes.h"

GameState::GameState(std::string stateID)
{
	stateNode = OgreManager::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	addEntities(EntityFactory::Instance()->createEntities(stateID,this));


}

	
GameState::~GameState()
{
	json j;
	for (auto p : scene) { p->save(j); }
	std::ofstream file("prueba.json");
	file << j;
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
	PhysicsManager::instance()->stepSimulation(time); //FÍSICA

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

	std::list<Component*>::iterator it = scene.begin();
	while (it != scene.end() && !handled) {
		if ((*it)->isActive())
			handled = (*it)->handleEvent(time);
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

std::list<Component*> GameState::getScene()
{
	return scene;
}

Ogre::SceneNode * GameState::getStateNode()
{
	return stateNode;
}
