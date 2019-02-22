#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <string>
#include <OgreVector3.h>

Ogre::Camera* createCamera(Ogre::SceneManager* scnMgn, std::string name, Ogre::Real NearClipDist, Ogre::Real FarClipDist, bool autoAspectRatio, Ogre::Real AspectRatio = 1.3);

