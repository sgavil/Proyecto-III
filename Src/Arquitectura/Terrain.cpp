#include "Terrain.h"


Terrain::Terrain()
{
}

Terrain::Terrain(std::string terrainFile)
{
	//name_ = Name::TerrainComp;
	terrainCreator_ = GestorRecursos::instance()->createTerrain(OgreSystem::instance()->getSM(), OgreSystem::instance()->getLight(), terrainFile);
}

Terrain::~Terrain()
{
	delete terrainCreator_;
}