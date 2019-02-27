#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <string>
#include <OgreMeshManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreVector3.h>
#include <OgrePlane.h>
#include <OgreEntity.h>
#include <OgreNode.h>
#include "JsonManager.h"
#include <OgreFileSystemLayer.h>
#include <OgreConfigFile.h>
#include <OgreTextureManager.h>

namespace GestorRecursos {

	Ogre::Camera* createCamera(Ogre::SceneManager* scnMgn, std::string name, Ogre::SceneNode* FatherNode,
		Ogre::Real NearClipDist, Ogre::Real FarClipDist,
		bool autoAspectRatio,  Ogre::Real AspectRatio = 1.3);

	Ogre::Entity* createPlane(Ogre::SceneManager* scnMgn, std::string name, std::string MaterialName,
							Ogre::Real width, Ogre::Real height, int Xsegments, int Ysegments,
							Ogre::SceneNode* FatherNode, std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	void initGestor();

	/*Metodo encargado de leer desde el resources.cfg o resources_d.cfg las rutas en las cuales queremos
	tener recursos. Despues de leerlas las inicializa en los respectivos grupos que definamos en los .cfg*/
	void initializeResources();
	
	JsonManager *jsonManager(void);
	 
}
