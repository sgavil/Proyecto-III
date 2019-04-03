#pragma once
#include "Component.h"


class Transform;
enum Shape;
class btVector3;
class btRigidBody;
class btTransform;

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

	//API
	//Add a force to the rigidBody
	virtual void addForce(Vector3 force);
	//Add a torque to the rigidbody
	virtual void addTorque(Vector3 torque);
	//Clears all current forces on the rigidbody
	virtual void clearForces();


	//Getters
	//Returns bounding box of the rigidbody, especified by minimum and maximum vectors
	void getAABB(Vector3& min, Vector3& max);
	//Returns mass of the rigidbody
	float getMass();

	//Returns linear velocity of the rigidbody
	Vector3 getLinearVelocity();
	//Returns angular velocity of the rigidbody
	Vector3 getAngularVelocity();


	//Returns total force of the rigidbody
	Vector3 getTotalForce();
	//Returns total torque of the rigidbody
	Vector3 getTotalTorque();

	//Tells whether the object is kinematic or not
	bool isKinematic();
	//Tells whether the object is static or not
	bool isStatic();


	//Setters
	//Sets linear velocity of the rigidbody
	void setLinearVelocity(Vector3 linearVel);
	//Sets angular velocity of the rigidbody
	void setAngularVelocity(Vector3 angVel);

	//Position
	//Returns rigidbody's position
	Vector3 getPosition();
	//Sets rigidbody's position
	void setPosition(Vector3 destiny);

	//Debug information
	//Returns a string with indented information of the rigidbody
	std::string getInfo();


protected:
	btRigidBody* rigid_;
	Transform* transform_;

	btTransform getBtTransform();
};

REGISTER_TYPE(Rigidbody)