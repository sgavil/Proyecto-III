#include "Terrain.h"
#include <iostream>
#include "OgreSystem.h"

#include <GestorRecursos/ResourceManager.h>

Terrain::Terrain():terrainCreator_(nullptr)
{
}

Terrain::Terrain(std::string terrainFile)
{
	terrainCreator_ = ResourceManager::instance()->createTerrain(OgreSystem::instance()->getSM(), OgreSystem::instance()->getLight(), terrainFile);
}

void Terrain::load(json file)
{
	terrainCreator_ = ResourceManager::instance()->createTerrain(OgreSystem::instance()->getSM(),
		OgreSystem::instance()->getLight(), file["file"]);
}

Terrain::~Terrain()
{
	delete terrainCreator_;
}