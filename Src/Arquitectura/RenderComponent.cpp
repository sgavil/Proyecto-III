#include "RenderComponent.h"



RenderComponent::RenderComponent(Ogre::SceneManager* manager, std::string meshName, Ogre::Vector3 position)
{
	//Nombre del componente
	name_ = Name::RenderComp;

	Ogre::Entity* ogreEntity = manager->createEntity(meshName);
	node_ = manager->getRootSceneNode()->createChildSceneNode();
	node_->attachObject(ogreEntity);
	node_->setPosition(position);
}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::update(unsigned int time)
{

}

bool RenderComponent::handleEvent(SDL_Event* e, unsigned int time)
{
	if (e->type == SDL_KEYDOWN)
	{
		//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
		if (e->key.keysym.sym == SDLK_SPACE)
		{
			//foo
		}
	}
	return false;
}
