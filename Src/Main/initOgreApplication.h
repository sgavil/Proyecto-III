

#pragma once
#include <OgreRoot.h>
#include "OgreRenderWindow.h"
#include <OgreViewport.h>
#include <OgreConfigFile.h>
#include <string>
#include <OgreLog.h>
#include <OgreTextureManager.h>
#include <OgreFileSystemLayer.h>
#include <OgreLight.h>
#include <iostream>
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreColourValue.h>
#include <OgreViewport.h>
#include <OgrePlane.h>
#include <OgreVector3.h>
#include "checkML.h"
#include <OgrePlane.h>

class initOgreApplication
{
public:

	initOgreApplication(Ogre::Root *root);
	~initOgreApplication();

	Ogre::SceneManager * getSceneManager();

private:

	Ogre::Root *root_;
	Ogre::RenderWindow *window_;
	Ogre::SceneManager *sceneMgr_;

	/*Elementos para definir la ventana*/
	const std::string APP_NAME = "ThemePark";
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	//Creando puerto de vista y camara
	Ogre::Camera *camera_;
	Ogre::Viewport *viewport_;

	Ogre::Light* light_;
	Ogre::SceneNode* lightNode_;
	Ogre::SceneNode* camNode_;

	Ogre::Entity* ogreEntity;
	Ogre::SceneNode* ogreNode_;

	Ogre::Plane plane_;

	/*Elementos para inicializar los recursos*/
	Ogre::FileSystemLayer* mFSLayer;

	/*Utiliza el root para crear una ventana de nombre APP_NAME , tamaño WINDOW_HEIGHT/WIDHT ademas de crear
	una camara y asociarle un viewport a esta*/
	void initWindow();

	/*Metodo encargado de leer desde el resources.cfg o resources_d.cfg las rutas en las cuales queremos
	tener recursos. Despues de leerlas las inicializa en los respectivos grupos que definamos en los .cfg*/
	void initializeResources();
};
