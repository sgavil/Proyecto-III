#include "RigidbodyComponent.h"



RigidbodyComponent::RigidbodyComponent(Ogre::SceneNode* node)
{
	name_ = Name::RigidComp;
	//CAJA
	btBoxShape* boxShape = new btBoxShape(btVector3(10, 10, 10));
	physicSystem::instance()->addShape(boxShape);

	Ogre::Vector3 pos = node->getPosition();
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));



	btDefaultMotionState *motionState = new btDefaultMotionState(startTransform);
	rigid = new btRigidBody(1, motionState, boxShape, btVector3(0, 0, 0));
	//box->setWorldTransform(startTransform);
	rigid->setRestitution(1);
	rigid->setUserPointer(node);


	physicSystem::instance()->addRigidBody(rigid);
}


RigidbodyComponent::~RigidbodyComponent()
{
}

void RigidbodyComponent::update(unsigned int time)
{
	if (hasNode())
	{
		btTransform trans;
		getTransform(&trans);
		btQuaternion orientation = trans.getRotation();
		Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(getNode());
		sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
		sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
	}
}
