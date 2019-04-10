#pragma once
#include "Component.h"
#include <OISKeyboard.h>
#include <OISMouse.h>

class Transform;
class Ogre::Camera;
class Ogre::SceneNode;

class Camera : public Component
{
public:
	Camera();
	~Camera();

	virtual void start();

	virtual void update(unsigned int time);

protected:
	//Pointer to the transform component
	Transform* transform_;

	//Ogre camera
	Ogre::SceneNode* camNode_;
	Ogre::Camera *camera_;
};

REGISTER_TYPE(Camera)