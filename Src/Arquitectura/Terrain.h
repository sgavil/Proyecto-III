#pragma once
#include "Component.h"
#include <iostream>
#include <GestorRecursos/gestorDeRecursos.h>
#include "OgreSystem.h"

class Terrain : public Component
{
public:
	Terrain(std::string terrainFile);
	~Terrain();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(SDL_Event* e, unsigned int time) { return false; }; //En realidad no haría falta ponerlo
	virtual void receive(Message* msg) {};

	TerrainCreator* terrainCreator_;
};