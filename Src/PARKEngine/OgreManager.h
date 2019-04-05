#pragma once
#include <string>
#include <memory>
#include <dirent.h>
#include <OgreRay.h>

//Espacio de nombres de Ogre
namespace Ogre
{
	class Light;
	class Plane;
	class Camera;
	class Entity;
	class RenderWindow;
	class SceneManager;
	class Root;
	class SceneNode;
	class MeshManager;
	class ResourceGroupManager;
	class TextureManager;
	class FileSystemLayer;
};

class TerrainGenerator;

class OgreManager
{
public:
	//"Constructora" de la instancia
	static OgreManager* instance(std::string initFileJson);

	//Devuelve la instancia
	static OgreManager* instance();

	~OgreManager();

	//Renderiza la escena (deltaTime debe estar en segundos)
	void render(unsigned int deltaTime);

	

	//Getters de los managers
	Ogre::SceneManager * getSceneManager();
	Ogre::MeshManager * getMeshManager();
	Ogre::ResourceGroupManager* getResourceGroupManager();
	Ogre::TextureManager* getTextureManager();
	Ogre::RenderWindow* getWindow() { return window_; };
	Ogre::Vector3 raycast();

	//Cración de recursos
	Ogre::FileSystemLayer* createFileSystemLayer(std::string cfLayerSystem);
	Ogre::Camera* createCamera(std::string name, Ogre::SceneNode* FatherNode, float NearClipDist, float FarClipDist, 
		bool autoAspectRatio, float AspectRatio = 1.3);	
	Ogre::Entity* createPlane(std::string name, std::string MaterialName, float width, float height, int Xsegments, int Ysegments,
		Ogre::SceneNode* FatherNode);
	TerrainGenerator* createTerrain(std::string terrainFile);

	//Eliminación de recursos
	void deleteFileSystemLayer(Ogre::FileSystemLayer* fsLayer);
	
	//Getters
	Ogre::Light* getLight() { return light_; };
	unsigned long gethWnd() { return hWnd; }

private:

	//Constructora privada
	OgreManager(std::string initFileJson);
	//Instancia
	static std::unique_ptr<OgreManager> instance_;
	

	Ogre::Root *root_;
	Ogre::RenderWindow *window_;
	Ogre::SceneManager *sceneMgr_;

	Ogre::Light* light_;

	Ogre::Plane* plane_;

	Ogre::Camera* camera_;
	//void ceguiInit();
	/*Utiliza el root para crear una ventana de nombre APP_NAME , tama�o WINDOW_HEIGHT/WIDHT ademas de crear
	una camara y asociarle un viewport a esta*/

	unsigned long hWnd; //Variable que toma la ventana de Ogre para aplicarla a la de SDL

	void initWindow(std::string initFileJson);
};
