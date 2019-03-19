#pragma once
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
#include <OgreConfigFile.h>
#include <OgreTextureManager.h>
#include <dirent.h>
#include <jsonParser.hpp>


using json = nlohmann::json;

class TerrainCreator;

class GestorRecursos 
{
public:
	~GestorRecursos();

	static GestorRecursos* instance();

	Ogre::Camera* createCamera(Ogre::SceneManager* scnMgn, std::string name, Ogre::SceneNode* FatherNode,
				Ogre::Real NearClipDist, Ogre::Real FarClipDist,
				bool autoAspectRatio,  Ogre::Real AspectRatio = 1.3);

	Ogre::Entity* createPlane(Ogre::SceneManager* scnMgn, std::string name, std::string MaterialName,
									Ogre::Real width, Ogre::Real height, int Xsegments, int Ysegments,
									Ogre::SceneNode* FatherNode, std::string groupName = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	TerrainCreator* createTerrain(Ogre::SceneManager* scnMgn, Ogre::Light* light, std::string terrainFile);

	void initializeResources();

	json getJsonByKey(const std::string &key);

private:
	GestorRecursos();

	static std::unique_ptr<GestorRecursos> instance_;

	void loadJsonsFiles(const std::string resourcesPath);
	void loadJson(const std::string &streamFilePath, const std::string &fileName);

	const std::string FOLDER_PATH = "Assets\\jsons\\";


	//Contenedores de los recursos
	std::map<std::string, json> jsonMap;

};