#include "GameState.h"
#include "PARKManagers.h"
#include "EntityFactory.h"
#include "Entity.h"
#include "Component.h"
#include "Button.h"
#include "OgreIncludes.h"

GameState::GameState(std::string stateID): id(stateID)
{
	stateNode = OgreManager::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();

	addEntities(EntityFactory::Instance()->createEntities(this));
}

	
GameState::~GameState()
{
	//Borra todas las entidades de la escena
	for (Entity* e : entities)
		removeEntity(e);
}

void GameState::start()
{
	for (Component* c : components)
		if (c->isActive())
			c->start();
}

void GameState::update(unsigned int time)
{
	PhysicsManager::instance()->stepSimulation(time); //FÍSICA

	//Actualizamos las entidades
	for (Component* c : components)
		if(c->isActive())
			c->update(time); 

	//Borramos las que lo hayan solicitado
	for (Entity* e : removedEntities)
		removeHard(e);
	removedEntities.clear();

	//InputManager::instance()->capture();
}

void GameState::render(unsigned int time)
{
	//OgreManager::instance()->render(time);
	for (Component* c : components)
		if (c->isActive())
			c->render(time);
}

bool GameState::handleInput(unsigned int time)
{
	bool handled = false;

	std::list<Component*>::iterator it = components.begin();
	while (it != components.end() && !handled) {
		if ((*it)->isActive())
			handled = (*it)->handleEvent(time);
		it++;
	}

	return false;
}

void GameState::addEntity(Entity* e)
{
	//Añadimos la entidad...
	entities.push_back(e);
	//Y sus componentes
	for (Component* c : e->getComponents()) 
		components.push_back(c);
}

void GameState::addEntities(std::vector<Entity*> ent)
{
	for (Entity* e : ent)
		addEntity(e);
}


bool GameState::removeEntity(std::string name)
{
	//Cogemos la entidad
	Entity* e = getEntity(name);

	if (e == nullptr) //Si no está, devolvemos false
		return false;

	//La borraremos luego
	removedEntities.push_back(e);
	return true;
}

bool GameState::removeEntity(Entity* e)
{
	//Comprobamos que de verdad esté
	std::list<Entity*>::iterator it = std::find(entities.begin(), entities.end(), e);
	if (it == entities.end())
		return false;

	//La borraremos luego
	removedEntities.push_back(e);
	return true;
}

void GameState::removeHard(Entity* e)
{
	//Borramos todos sus componentes...
	for (Component* c : e->getComponents())
	{
		components.remove(c); //Lo quitamos de la escena
		e->delComponent(c); //Se lo quitamos a la entidad
		delete c; //Lo eliminamos
		c = nullptr;
	}

	//La borramos a ella
	entities.remove(e);
	delete e;
	e = nullptr;
}

Entity* GameState::getEntity(std::string name)
{
	Entity* e = nullptr;
	std::list<Entity*>::iterator it = entities.begin();

	// Buscamos al primer componente que tenga esa entidad
	while (it != entities.end() && e == nullptr)
	{
		if ((*it)->getName() == name)
			e = (*it);
		it++;
	}

	return e;
}

std::list<Component*> GameState::getComponents()
{
	return components;
}

Ogre::SceneNode * GameState::getStateNode()
{
	return stateNode;
}
