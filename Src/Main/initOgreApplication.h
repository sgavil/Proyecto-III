#pragma once
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreLog.h>
//#include <OgreFileSystemLayer.h>
#include <OgreLight.h>
#include <iostream>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreColourValue.h>
#include <OgrePlane.h>
#include <GestorRecursos/gestorDeRecursos.h>
#include <OgreMeshManager.h>
#include <OgreResourceGroupManager.h>
#include <GestorRecursos/JsonManager.h>
//CEGUI
#include <CEGUI/RendererModules/Ogre/Renderer.h>


class initOgreApplication
{
public:

	initOgreApplication(Ogre::Root *root, std::string initFileJson);
	~initOgreApplication();

	Ogre::SceneManager * getSceneManager();
	//Metodos getter
	Ogre::RenderWindow* getWindow() { return window_; };
	Ogre::Light* getLight() { return light_; };

private:

	Ogre::Root *root_;
	Ogre::RenderWindow *window_;
	Ogre::SceneManager *sceneMgr_;

	Ogre::Light* light_;

	Ogre::Plane plane_;

	json initFile;
	/*Utiliza el root para crear una ventana de nombre APP_NAME , tamaño WINDOW_HEIGHT/WIDHT ademas de crear
	una camara y asociarle un viewport a esta*/
	void initWindow();
};
