#include "Camera.h"



Camera::Camera()
{
	name_ = Name::CameraComp;

	camNode_ = OgreSystem::instance()->getSM()->getRootSceneNode()->createChildSceneNode("camNode");
	camera_ = GestorRecursos::createCamera(OgreSystem::instance()->getSM(), "cam", camNode_, 5, 50000, true);
	camNode_->setPosition(0, 2000, 1500);
	camNode_->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	viewport_ = OgreSystem::instance()->getWindow()->addViewport(camera_);
	viewport_->setClearEveryFrame(true);
}


Camera::~Camera()
{
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
