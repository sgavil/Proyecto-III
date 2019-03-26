#pragma once
#include "Component.h"


class Transform;
enum Shape;
class btVector3;
class btRigidBody;

class Rigidbody : public Component
{
public:
	Rigidbody();

	//Constructoras para Rigidbodys asociados a una malla
	Rigidbody(Transform* transform, Shape shape, float mass = 1);

	~Rigidbody();

	virtual void start();
	
	virtual void load(json file);

	//Generic methods
	virtual void update(unsigned int time);

	//Add a force to the rigidBody
	virtual void addForce(btVector3 force);

protected:
	btRigidBody* rigid_;
	Transform* transform_;
};

REGISTER_TYPE(Rigidbody)