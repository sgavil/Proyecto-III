#pragma once
#include "Component.h"
#include <iostream>
#include "physicSystem.h"
#include <OgreSceneNode.h>
#include "Transform.h"

class Rigidbody : public Component
{
public:
	Rigidbody();

	//Constructoras para Rigidbodys asociados a una malla
	Rigidbody(Transform* transform, Shape shape, btScalar mass = 1);

	~Rigidbody();

	virtual void start();
	
	virtual void load(json file);

	//Generic methods
	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(unsigned int time);
	virtual void receive(Message* msg) {};

	//Add a force to the rigidBody
	virtual void addForce(btVector3 force) { rigid_->applyCentralImpulse(force); };

protected:
	btRigidBody* rigid_;
	Transform* transform_;
};

REGISTER_TYPE(Rigidbody)