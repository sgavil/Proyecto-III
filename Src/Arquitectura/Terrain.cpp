#include "Terrain.h"
#include <iostream>
#include "OgreSystem.h"

#include <GestorRecursos/ResourceManager.h>

Terrain::Terrain():terrainCreator_(nullptr)
{
}

Terrain::Terrain(std::string terrainFile)
{
	terrainCreator_ = OgreSystem::instance()->createTerrain(terrainFile);
}

void Terrain::load(json file)
{
	terrainCreator_ = OgreSystem::instance()->createTerrain(file["file"]);
}

Terrain::~Terrain()
{
	delete terrainCreator_;
}