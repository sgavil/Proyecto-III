#include "Terrain.h"

Terrain::Terrain(std::string terrainFile)
{
	name_ = Name::TerrainComp;
	terrainCreator_ = GestorRecursos::createTerrain(OgreSystem::instance()->getSM(), OgreSystem::instance()->getLight(), terrainFile);
}

Terrain::~Terrain()
{
	delete terrainCreator_;
}
