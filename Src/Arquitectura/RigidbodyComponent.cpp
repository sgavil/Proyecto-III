#include "RigidbodyComponent.h"



RigidbodyComponent::RigidbodyComponent(Ogre::SceneNode* node, Shape shape, btScalar dimensions, btScalar mass)
{
	//TODO: que el tamaño del COllider se ajuste al tamaño de la malla de la entidad que tiene el nodo
	//Nombre del componente
	name_ = Name::RigidComp;

	//Creamos el Rigidbody
	btVector3 pos = btVector3 ( node->getPosition().x, node->getPosition().y, node->getPosition().z );
	rigid_ = physicSystem::createRigidBody(shape, pos, dimensions, mass);

	//Lo asociamos al nodo en cuestión
	if(node != nullptr)
		rigid_->setUserPointer(node);
}

RigidbodyComponent::RigidbodyComponent(Ogre::Vector3 position, Shape shape, btScalar dimensions, btScalar mass)
{
	//Nombre del componente
	name_ = Name::RigidComp;

	//Creamos el Rigidbody
	btVector3 pos = btVector3(position.x, position.y, position.z);
	rigid_ = physicSystem::createRigidBody(shape, pos, dimensions, mass);
}


RigidbodyComponent::~RigidbodyComponent()
{
}

void RigidbodyComponent::update(unsigned int time)
{
	//Si está asociado a un nodo
	if (rigid_->getUserPointer() != nullptr)
	{
		//Obtenemos su posición y orientación
		btTransform trans;
		rigid_->getMotionState()->getWorldTransform(trans);
		btQuaternion orientation = trans.getRotation();

		//Pillamos el nodo de Ogre
		Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(rigid_->getUserPointer());

		//Actualizamos la posición y orientación del nodo de Ogre en función a las del Rigidbody
		sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
		sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
	}
}

bool RigidbodyComponent::handleEvent(SDL_Event* e, unsigned int time)
{
	if (e->type == SDL_KEYDOWN)
	{
		//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
		if (e->key.keysym.sym == SDLK_SPACE)
		{
			rigid_->applyCentralImpulse(btVector3(500, 0, 0));
			return true;
		}
	}
	return false;
}
