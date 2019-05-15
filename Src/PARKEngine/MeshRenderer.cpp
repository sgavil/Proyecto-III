#include "MeshRenderer.h"

#include "Entity.h"
#include "Transform.h"


#include "OgreIncludes.h"
#include "OgreManager.h"
#include <iostream>
#include "GameState.h"

MeshRenderer::MeshRenderer(): node_(nullptr)
{
}

MeshRenderer::MeshRenderer(std::string meshName, bool visible)
{
	Ogre::Entity* ogreEntity = OgreManager::instance()->getSceneManager()->createEntity(meshName);
	node_ = EntityFactory::Instance()->get_currentState()->getStateNode()->createChildSceneNode();
	node_->attachObject(ogreEntity);
	node_->setVisible(visible);
}

void MeshRenderer::load(json file)
{
	std::string meshName;
	addParameter(meshName, file["mesh"]);


	Ogre::Entity* ogreEntity = OgreManager::instance()->getSceneManager()->createEntity(meshName);
		node_ = EntityFactory::Instance()->get_currentState()->getStateNode()->createChildSceneNode();

	//node_ = OgreManager::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode(); //AQUI TIENE QUE COLGAR DEL NODO SCENA
	node_->attachObject(ogreEntity);

	std::string material;
	if (addParameter(material, file["material"]))
		setMaterial(material);

	node_->setVisible(file["visible"]);
}


MeshRenderer::~MeshRenderer()
{
	
}

void MeshRenderer::start()
{
	Transform* transform_ = entity_->getComponent<Transform>();
	if (transform_ == nullptr)
		std::cout << "ERROR: ENTITY " + entity_->getName() + " IS LACKING TRANSFORM COMPONENT" << std::endl;
	else
	{
		node_->setPosition(transform_->getPosition());
		node_->setOrientation(transform_->getRotation());
		node_->setScale(transform_->getScale());
	}
	node_->_update(false, false);
}

Ogre::SceneNode * MeshRenderer::getNode()
{
	 return node_; 
}

void MeshRenderer::setVisible(bool b)
{
	node_->setVisible(b);
}

void MeshRenderer::setMaterial(std::string materialName)
{
	if (!node_->getAttachedObjects().empty())
		((Ogre::Entity*)node_->getAttachedObject(0))->setMaterialName(materialName);
	else
		std::cout << "CAN'T ASSIGN MATERIAL, LACKING OGRE ENTITY" << std::endl;
}

std::string MeshRenderer::getMaterial()
{
	return ((Ogre::Entity*)node_->getAttachedObject(0))->getSubEntities()[0]->getMaterialName();
}

void MeshRenderer::getAABB(Vector3& aabbMin, Vector3& aabbMax)
{
	Ogre::AxisAlignedBox box = node_->_getWorldAABB();
	aabbMin = box.getMinimum();
	aabbMax = box.getMaximum();
}

void MeshRenderer::receive(Message* msg)
{
	if (msg->mType_ == MessageId::TRANSFORM_CHANGED)
	{
		TransformChanged* transChanged = static_cast<TransformChanged*>(msg);
		Transform* t = transChanged->transform_;

		node_->setPosition(t->getPosition());
		node_->setOrientation(t->getRotation());
		node_->setScale(t->getScale());
	}
}
