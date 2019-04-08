#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include <SDL_video.h>

#include "ResourceManager.h"
#include "InputManager.h"

#include "OgreIncludes.h"
#include "OgreManager.h"

#include <CEGUI/CEGUI.h>


Camera::Camera()
{
	camNode_ = OgreManager::instance()->getCameraNode();
	camera_ = OgreManager::instance()->getCamera();
	viewport_ = OgreManager::instance()->getViewport();

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
		Vector3 pos = transform_->getPosition();
		camNode_->setPosition(pos);
		camNode_->lookAt(Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	}
}

void Camera::update(unsigned int time)
{
	
}

bool Camera::handleEvent(unsigned int time)
{
		if (InputManager::getSingletonPtr()->isKeyDown("Avanzar"))
			camNode_->translate({ 0, 0, -10 }, Ogre::Node::TS_WORLD);
		if (InputManager::getSingletonPtr()->isKeyDown("Retroceder"))
			camNode_->translate({ 0, 0, 10 }, Ogre::Node::TS_WORLD);
		if (InputManager::getSingletonPtr()->isKeyDown("MoverIzquierda"))
			camNode_->translate({ -10, 0, 0 }, Ogre::Node::TS_WORLD);
		if (InputManager::getSingletonPtr()->isKeyDown("MoverDerecha"))
			camNode_->translate({ 10, 0, 0 }, Ogre::Node::TS_WORLD);
		if (InputManager::getSingletonPtr()->isKeyDown("Ampliar"))
			camNode_->translate({ 0, -10, 0 }, Ogre::Node::TS_WORLD);
		if (InputManager::getSingletonPtr()->isKeyDown("Desampliar"))
			camNode_->translate({ 0, 10, 0 }, Ogre::Node::TS_WORLD);
		if (InputManager::getSingletonPtr()->isKeyDown("Ray")) 	OgreManager::instance()->raycast();
		return false;
}
