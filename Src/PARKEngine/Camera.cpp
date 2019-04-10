#include "Camera.h"

#include "Entity.h"
#include "Transform.h"

#include "OgreManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "OgreIncludes.h"


#include <CEGUI/CEGUI.h>
#include <SDL_video.h>


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::start()
{
	//Camera already created
	if (OgreManager::instance()->getCamera() != nullptr)
		camera_ = OgreManager::instance()->getCamera();
	//Create a new one
	else
		camera_ = OgreManager::instance()->createCamera("Camera", 5, 50000, true);


	camNode_ = (Ogre::SceneNode*)camera_->getParentNode();
	camera_->getViewport()->setClearEveryFrame(true);
	//Initialises it 
	transform_ = entity_->getComponent<Transform>();
	if (transform_ == nullptr)
		std::cout << "ERROR: ENTITY " + entity_->getName() + " IS LACKING TRANSFORM COMPONENT" << std::endl;
	//Initialise camNode
	else
	{
		Vector3 pos = transform_->getPosition();
		camNode_->setPosition(pos);
		camNode_->lookAt(Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
		transform_->setRotation(camNode_->getOrientation());
	}
}

void Camera::update(unsigned int time)
{

}

void Camera::receive(Message* msg)
{
	if(msg->mType_ == MessageId::TRANSFORM_CHANGED)
	{
		camNode_->setPosition(transform_->getPosition());
		camNode_->setOrientation(transform_->getRotation());
	}
}