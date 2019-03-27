#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <SDL_video.h>
#include "OgreSystem.h"
#include <iostream>
#include <GestorRecursos/gestorDeRecursos.h>
#include "InputManager.h"

Camera::Camera()
{
	camNode_ = OgreSystem::instance()->getSM()->getRootSceneNode()->createChildSceneNode("camNode");
	camera_ = GestorRecursos::instance()->createCamera(OgreSystem::instance()->getSM(), "cam", camNode_, 5, 50000, true);
	viewport_ = OgreSystem::instance()->getWindow()->addViewport(camera_);
	viewport_->setClearEveryFrame(true);

	InputManager::getSingletonPtr()->addKeyListener(this, "Camera");
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
	return false;
}

bool Camera::keyPressed(const OIS::KeyEvent & arg)
{
	switch (arg.key)
	{
	case OIS::KC_W:
		camNode_->translate({ 0,0,-10 }, Ogre::Node::TS_WORLD);
	}
	return true;
}