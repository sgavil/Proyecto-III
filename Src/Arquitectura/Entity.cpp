#include "Entity.h"


Entity::Entity()
{
}

void Entity::addComponent(Component comp)
{
	components_.push_back(comp);
}

void Entity::delComponent(Component comp)
{
	
}


Entity::~Entity()
{	
}
