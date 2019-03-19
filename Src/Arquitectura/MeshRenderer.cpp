#include "MeshRenderer.h"
#include "Entity.h"


MeshRenderer::MeshRenderer()
{
}

MeshRenderer::MeshRenderer(std::string meshName, bool visible)
{
	//Nombre del componente
	//name_ = Name::MeshRendererComp;

	Ogre::Entity* ogreEntity = OgreSystem::instance()->getSM()->createEntity(meshName);
	node_ = OgreSystem::instance()->getSM()->getRootSceneNode()->createChildSceneNode();
	node_->attachObject(ogreEntity);
	node_->setVisible(visible);
}


MeshRenderer::~MeshRenderer()
{
	
}

void MeshRenderer::start()
{
	transform_ = entity_->getComponent<Transform>();
	if (transform_ == nullptr)
		std::cout << "ERROR: ENTITY " + entity_->getName() + " IS LACKING TRANSFORM COMPONENT" << std::endl;
}

void MeshRenderer::update(unsigned int time)
{
	if(transform_ != nullptr)
	{
		node_->setPosition(transform_->getPosition());
		node_->setOrientation(transform_->getOrientation());
		node_->setScale(transform_->getScale());
	}
}

bool MeshRenderer::handleEvent(SDL_Event* e, unsigned int time)
{
	if (e->type == SDL_KEYDOWN)
	{
		//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
		if (e->key.keysym.sym == SDLK_v)
		{
			node_->flipVisibility();
			//foo
		}
	}
	return false;
}
