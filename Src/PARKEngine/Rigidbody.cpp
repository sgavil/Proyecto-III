#include "Rigidbody.h"

#include "Entity.h"
#include "Transform.h"
#include "PhysicsManager.h"
#include <iostream>
#include "btBulletDynamicsCommon.h"



Rigidbody::Rigidbody() : transform_(nullptr), rigid_(nullptr)
{
}


Rigidbody::Rigidbody(Transform* transform, Shape shape, float mass) : transform_(transform)
{
	//Creamos el rigidbody
	rigid_ = PhysicsManager::createRigidBody(shape, transform_->getScale(), mass);
}


void Rigidbody::load(json file)
{
	json dimensions = file["dimensions"];
	Vector3 dims;
	dims.x = dimensions["x"];
	dims.y = dimensions["y"];
	dims.z = dimensions["z"];

	rigid_ = PhysicsManager::createRigidBody(BoxShape, dims, file["mass"]);
}

void Rigidbody::start()
{
	transform_ = entity_->getComponent<Transform>();
	if (transform_ == nullptr)
		std::cout << "ERROR: ENTITY " + entity_->getName() + " IS LACKING TRANSFORM COMPONENT" << std::endl;
	else
	{
		rigid_->setUserPointer(transform_);

		//Colocamos en un inicio al rigidbody en el lugar del Transform de la entidad
		btTransform trans;
		trans.setIdentity();
		trans.setOrigin(btVector3(transform_->getPosition().x, transform_->getPosition().y, transform_->getPosition().z));
		
		rigid_->setWorldTransform(trans);
	}
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::update(unsigned int time)
{
	//Si está asociado a un transform
	if(transform_ != nullptr)
	{

		//Obtenemos su posición y orientación
		btTransform trans;
		if (rigid_->getMotionState())
			rigid_->getMotionState()->getWorldTransform(trans);
		else
			trans = rigid_->getWorldTransform();

		//Actualizamos la posición y orientación del nodo de Ogre en función a las del Rigidbody
		transform_->setPosition(Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
		transform_->setOrientation(Quaternion(trans.getRotation().getW(), trans.getRotation().getX(),
			trans.getRotation().getY(), trans.getRotation().getZ()));
	}
}

void Rigidbody::addForce(btVector3 force)
{
	rigid_->applyCentralImpulse(force);
}
