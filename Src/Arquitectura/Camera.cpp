#include "Camera.h"
#include "Entity.h"


Camera::Camera()
{
	camNode_ = OgreSystem::instance()->getSM()->getRootSceneNode()->createChildSceneNode("camNode");
	camera_ = GestorRecursos::instance()->createCamera(OgreSystem::instance()->getSM(), "cam", camNode_, 5, 50000, true);
	viewport_ = OgreSystem::instance()->getWindow()->addViewport(camera_);
	viewport_->setClearEveryFrame(true);
}


Camera::~Camera()
{
}

void Camera::start()
{
	transform_ = entity_->getComponent<Transform>();
	if (transform_ == nullptr)
		std::cout << "ERROR: ENTITY " + entity_->getName() + " IS LACKING TRANSFORM COMPONENT" << std::endl;
	else
	{
		Ogre::Vector3 pos = transform_->getPosition();
		camNode_->setPosition(pos);
		camNode_->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	}
}

void Camera::update(unsigned int time)
{
	
}

bool Camera::handleEvent(SDL_Event* e, unsigned int time)
{
	if (e->type == SDL_KEYDOWN)
	{
		//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
		if (e->key.keysym.sym == SDLK_UP)
		{
			std::cout << "Hola! Funciono Desde un componente" << std::endl;
			return true;
		}
	}
	return false;
}
