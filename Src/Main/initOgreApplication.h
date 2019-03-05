#pragma once
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreLog.h>
#include <OgreFileSystemLayer.h>
#include <OgreLight.h>
#include <iostream>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreColourValue.h>
#include <OgrePlane.h>
#include "checkML.h"
#include <OgrePlane.h>
#include <GestorRecursos/gestorDeRecursos.h>
#include <OgreMeshManager.h>
#include <OgreResourceGroupManager.h>


class initOgreApplication
{
public:

	initOgreApplication(Ogre::Root *root, std::string initFileJson);
	~initOgreApplication();

	Ogre::SceneManager * getSceneManager();
	//Metodos getter
	Ogre::RenderWindow* getWindow() { return window_; };

private:

	Ogre::Root *root_;
	Ogre::RenderWindow *window_;
	Ogre::SceneManager *sceneMgr_;

	//Creando puerto de vista y camara
	//Ogre::Camera *camera_;
	//Ogre::Viewport *viewport_;

	Ogre::Light* light_;
	Ogre::SceneNode* lightNode_;
	//Ogre::SceneNode* camNode_;

	Ogre::Entity* ogreEntity;
	Ogre::SceneNode* ogreNode_;

	Ogre::Plane plane_;
	Ogre::Entity* suelo_;
	Ogre::SceneNode* sueloNodo_;

	/*Elementos para inicializar los recursos*/
	Ogre::FileSystemLayer* mFSLayer;

	json initFile;
	/*Utiliza el root para crear una ventana de nombre APP_NAME , tamaño WINDOW_HEIGHT/WIDHT ademas de crear
	una camara y asociarle un viewport a esta*/
	void initWindow();


	//Métodos para la prueba del terreno
	TerrainManager* terrainManager_;
};
