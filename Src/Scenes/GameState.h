#pragma once
#include <Arquitectura/Entity.h>

class Component;

class GameState
{
protected:
	std::vector<Component*> scene; // Componentes en la escena

public:
	GameState(json file);
	virtual ~GameState();

	virtual void update(unsigned int time);
	virtual void render(unsigned int time);
	virtual bool handleInput(unsigned int time);

	//Añade una entidad a la escena
	void addEntity(Entity* e);

	//Elimina una entidad de la escena. Devuelve true si estaba en la escena, false e.o.c
	bool removeEntity(std::string name);

	//Devuelve una entidad de la escena
	Entity* getEntity(std::string name);

	//Devuelve la escena
	std::vector<Component*> getScene() { return scene; }; //TODO: replantearse este método
};