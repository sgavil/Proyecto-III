#pragma once
#include "Component.h"
#include <iostream>
#include <GestorRecursos/gestorDeRecursos.h>
#include "OgreSystem.h"

class Terrain : public Component
{
public:
	Terrain();
	Terrain(std::string terrainFile);
	~Terrain();


	virtual void load(json file);

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(unsigned int time) { return false; }; //En realidad no haría falta ponerlo
	virtual void receive(Message* msg) {};

	TerrainGenerator* terrainCreator_;
};

REGISTER_TYPE(Terrain)