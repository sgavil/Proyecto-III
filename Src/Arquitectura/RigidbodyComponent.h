#pragma once
#include "Component.h""
#include <SDL.h>
#include <iostream>
#include "physicSystem.h"
#include <OgreRoot.h>
#include <OgreSceneNode.h>


class RigidbodyComponent : public Component
{
public:
	RigidbodyComponent(Ogre::SceneNode* node);
	~RigidbodyComponent();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual void handleEvent() {};
	virtual void receive(Message* msg) {};

	virtual bool hasNode() { return (rigid->getUserPointer() != nullptr); };
	virtual void* getNode() { return rigid->getUserPointer(); };
	virtual void getTransform(btTransform* trans) { return rigid->getMotionState()->getWorldTransform(*trans); };

protected:
	btRigidBody* rigid;

};

