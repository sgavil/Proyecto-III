

#pragma once
#include <OgreRoot.h>
#include "OgreRenderWindow.h"
#include <OgreConfigFile.h>
#include <OgreLog.h>
#include <OgreTextureManager.h>
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
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <jsonParser.hpp>

using json = nlohmann::json;

class initOgreApplication
{
public:

	initOgreApplication(Ogre::Root *root, const json& initFile);
	~initOgreApplication();

	Ogre::SceneManager * getSceneManager();
	//Metodos getter
	Ogre::RenderWindow* getWindow() { return window_; };

private:

	Ogre::Root *root_;
	Ogre::RenderWindow *window_;
	Ogre::SceneManager *sceneMgr_;

	//Creando puerto de vista y camara
	Ogre::Camera *camera_;
	Ogre::Viewport *viewport_;

	Ogre::Light* light_;
	Ogre::SceneNode* lightNode_;
	Ogre::SceneNode* camNode_;

	Ogre::Entity* ogreEntity;
	Ogre::SceneNode* ogreNode_;

	Ogre::Plane plane_;
	Ogre::Entity* suelo_;
	Ogre::SceneNode* sueloNodo_;

	/*Elementos para inicializar los recursos*/
	Ogre::FileSystemLayer* mFSLayer;

	/*Utiliza el root para crear una ventana de nombre APP_NAME , tamaño WINDOW_HEIGHT/WIDHT ademas de crear
	una camara y asociarle un viewport a esta*/
	void initWindow(json initFile);

	/*Metodo encargado de leer desde el resources.cfg o resources_d.cfg las rutas en las cuales queremos
	tener recursos. Despues de leerlas las inicializa en los respectivos grupos que definamos en los .cfg*/
	void initializeResources();


	//Métodos para la prueba del terreno
	void defineTerrain(long x, long y);
	void initBlendMaps(Ogre::Terrain* terrain);
	void configureTerrainDefaults(Ogre::Light* light);
	void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img);



	bool mTerrainsImported;
	Ogre::TerrainGroup* mTerrainGroup;
	Ogre::TerrainGlobalOptions* mTerrainGlobals;
};
