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
	camNode_ = OgreManager::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("camNode");
	camera_ = OgreManager::instance()->createCamera("cam", camNode_, 5, 50000, true);
	viewport_ = OgreManager::instance()->getWindow()->addViewport(camera_);
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
	if (InputManager::getSingletonPtr()->isKeyDown("Ray"))
	{
		Ogre::Ray r = camera_->getCameraToViewportRay(
			CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_x/
			float(OgreManager::instance()->getWindow()->getWidth()),
			CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_y/
			float(OgreManager::instance()->getWindow()->getHeight()));
		OgreManager::instance()->raycast(r);
	}
	return false;
}



