#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include <SDL_video.h>
#include <iostream>
#include <GestorRecursos/ResourceManager.h>
#include "InputManager.h"

#include "OgreIncludes.h"
#include "OgreSystem.h"


Camera::Camera()
{
	camNode_ = OgreSystem::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("camNode");
	camera_ = OgreSystem::instance()->createCamera("cam", camNode_, 5, 50000, true);
	viewport_ = OgreSystem::instance()->getWindow()->addViewport(camera_);
	viewport_->setClearEveryFrame(true);

	//InputManager::getSingletonPtr()->addKeyListener(this, "Camera");
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

bool Camera::handleEvent(unsigned int time)
{
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_W))
		camNode_->translate({ 0, 0, -10 }, Ogre::Node::TS_WORLD);
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_S))
		camNode_->translate({ 0, 0, 10 }, Ogre::Node::TS_WORLD);
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_A))
		camNode_->translate({ -10, 0, 0 }, Ogre::Node::TS_WORLD);
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_D))
		camNode_->translate({ 10, 0, 0 }, Ogre::Node::TS_WORLD);
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_E))
		camNode_->translate({ 0, -10, 0 }, Ogre::Node::TS_WORLD);
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_Q))
		camNode_->translate({ 0, 10, 0 }, Ogre::Node::TS_WORLD);
	return false;
}



