#include "TerrainComponent.h"

TerrainComponent::TerrainComponent(std::string terrainFile)
{
	name_ = Name::TerrainComp;
	terrainCreator_ = GestorRecursos::createTerrain(OgreSystem::instance()->getSM(), OgreSystem::instance()->getLight(), terrainFile);
}

TerrainComponent::~TerrainComponent()
{
	delete terrainCreator_;
}
