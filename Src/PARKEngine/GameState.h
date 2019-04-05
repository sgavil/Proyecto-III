#pragma once
#include <vector>
#include <list>

class Component;
class Entity;

class GameState
{
protected:
	std::list<Component*> scene; // Componentes de la escena

public:
	GameState(std::string stateID);
	virtual ~GameState();

	virtual void start();

	virtual void update(unsigned int time);
	virtual void render(unsigned int time);
	virtual bool handleInput(unsigned int time);

	// ·> Añade una entidad a la escena
	void addEntity(Entity* e);

	// ·> Añade un grupo de entidades a la escena 
	void addEntities(std::vector<Entity*> ent);

	// ·> Elimina una entidad de la escena. Devuelve 'true' si estaba en la escena, 'false' e.o.c
	bool removeEntity(std::string name);

	// ·> Devuelve una entidad de la escena
	Entity* getEntity(std::string name);
	// ·> Devuelve la escena
	std::list<Component*> getScene();
};