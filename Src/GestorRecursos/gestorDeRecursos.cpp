#include "gestorDeRecursos.h"

Ogre::Camera* createCamera(Ogre::SceneManager* scnMgn, std::string name, Ogre::Real NearClipDist, Ogre::Real FarClipDist, bool autoAspectRatio, Ogre::Real AspectRatio)
{
	Ogre::Camera* cam_ = scnMgn->createCamera(name);
	cam_->setNearClipDistance(NearClipDist);
	cam_->setFarClipDistance(FarClipDist);
	if(autoAspectRatio)cam_->setAutoAspectRatio(autoAspectRatio);
	else cam_->setAspectRatio(AspectRatio);
	return cam_;
}

