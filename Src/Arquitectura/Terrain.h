#pragma once
#include "Component.h"

class Terrain : public Component
{
public:
	Terrain();
	Terrain(std::string terrainFile);
	~Terrain();

	virtual void load(json file);

	TerrainGenerator* terrainCreator_;
};

REGISTER_TYPE(Terrain)