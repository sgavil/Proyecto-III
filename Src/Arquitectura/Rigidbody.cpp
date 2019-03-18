#include "Rigidbody.h"
#include "Entity.h"



Rigidbody::Rigidbody()
{
}


Rigidbody::Rigidbody(Transform* transform, Shape shape, btScalar mass) : transform_(transform)
{
	//TODO: que el tamaño del COllider se ajuste al tamaño de la malla de la entidad que tiene el nodo
	//Nombre del componente
	name_ = Name::RigidbodyComp;

	//Creamos el rigidbody
	rigid_ = physicSystem::createRigidBody(shape, transform_->getScale(), mass);
}

void Rigidbody::start()
{
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
		/*btVector3 min, max;
		 rigid_->getAabb(min, max);
		 std::cout << "[" << (max - min).getX() << ", " << (max - min).getY() << ", " << (max - min).getZ() << "]" << std::endl;*/

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

bool Rigidbody::handleEvent(SDL_Event* e, unsigned int time)
{
	if (e->type == SDL_KEYDOWN)
	{
		//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
		if (e->key.keysym.sym == SDLK_SPACE)
		{
			//rigid_->applyImpulse(btVector3(0, 20, 0), btVector3(100, 0, 0));
			rigid_->applyCentralImpulse(btVector3(0, 100, 0));
			return true;
		}
	}
	return false;
}
