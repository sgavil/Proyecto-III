#pragma once
#include <OgreRoot.h>
#include "OgreRenderWindow.h"
#include <OgreViewport.h>

class initOgreApplication
{
public:
	initOgreApplication(Ogre::Root *root);
	~initOgreApplication();

private:
	Ogre::Root *root_;
	Ogre::RenderWindow *window_;
	Ogre::SceneManager *sceneMgr_;
	
	//Creando puerto de vista y camara
	Ogre::Camera *camera_;
	Ogre::Viewport *viewport_;

	void initWindow();
};

