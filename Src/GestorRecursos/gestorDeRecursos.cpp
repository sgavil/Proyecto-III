#include "gestorDeRecursos.h"

Ogre::Camera*  GestorRecursos::createCamera(Ogre::SceneManager* scnMgn, std::string name, Ogre::SceneNode* FatherNode, Ogre::Real NearClipDist, Ogre::Real FarClipDist, bool autoAspectRatio, Ogre::Real AspectRatio)
{
	Ogre::Camera* cam_ = scnMgn->createCamera(name);
	cam_->setNearClipDistance(NearClipDist);
	cam_->setFarClipDistance(FarClipDist);
	FatherNode->attachObject(cam_);
	if(autoAspectRatio)cam_->setAutoAspectRatio(autoAspectRatio);
	else cam_->setAspectRatio(AspectRatio);
	return cam_;
}

Ogre::Entity * GestorRecursos::createPlane(Ogre::SceneManager * scnMgn, std::string name, std::string MaterialName, Ogre::Real width, Ogre::Real height, int Xsegments, int Ysegments, Ogre::SceneNode* FatherNode, std::string groupName)
{
	Ogre::Entity* plane;
	Ogre::MeshManager::getSingleton().createPlane(name, groupName, Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), width, height,
		Xsegments, Ysegments, true, 1, 1.0, 1.0, Ogre::Vector3::NEGATIVE_UNIT_Z);
	plane = scnMgn->createEntity(name);
	plane->setMaterialName(MaterialName);
	FatherNode->attachObject(plane);
	return plane;
}
