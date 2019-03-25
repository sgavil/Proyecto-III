#include "Terrain.h"


Terrain::Terrain():terrainCreator_(nullptr)
{
}

Terrain::Terrain(std::string terrainFile)
{
	terrainCreator_ = GestorRecursos::instance()->createTerrain(OgreSystem::instance()->getSM(), OgreSystem::instance()->getLight(), terrainFile);
}

void Terrain::load(json file)
{
	terrainCreator_ = GestorRecursos::instance()->createTerrain(OgreSystem::instance()->getSM(),
		OgreSystem::instance()->getLight(), file["file"]);
}

Terrain::~Terrain()
{
	delete terrainCreator_;
}