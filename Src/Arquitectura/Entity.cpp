#include "Entity.h"


Entity::Entity()
{
	//Poner el RigidBody a nullptr
}

Entity::Entity(std::vector<Component*> comps) //, RigidBody* r)
{
	//Creamos la entidad con los componentes dados, llamando a addComponent
	for (Component* c : comps)
		addComponent(c);
	//rigid_ = r;
}


void Entity::addComponent(Component* comp)
{
	//Metemos el componente en el vector y avisamos al componente desde nuestra entidad
	components_.push_back(comp);
	comp->setEntity(this);
}

bool Entity::delComponent(Component* comp)
{
	//Buscamos el componente en cuestión
	std::vector<Component*>::iterator it;
	it = std::find(components_.begin(), components_.end(), comp);
	//Si lo encuentra, lo elimina de su lista y lo notifica
	if (it != components_.end())
	{
		components_.erase(it);
		return true;
	}
	return false;
}


Entity::~Entity()
{
}
