#include "gestorDeRecursos.h"
#include "TerrainCreator.h"
#include <OgreFileSystemLayer.h>

std::unique_ptr<GestorRecursos> GestorRecursos::instance_;

Ogre::Camera*  GestorRecursos::createCamera(Ogre::SceneManager* scnMgn, std::string name, Ogre::SceneNode* FatherNode, Ogre::Real NearClipDist, Ogre::Real FarClipDist, bool autoAspectRatio, Ogre::Real AspectRatio)
{
	Ogre::Camera* cam_ = scnMgn->createCamera(name);
	cam_->setNearClipDistance(NearClipDist);
	cam_->setFarClipDistance(FarClipDist);
	FatherNode->attachObject(cam_);
	if(autoAspectRatio)cam_->setAutoAspectRatio(autoAspectRatio);
	else cam_->setAspectRatio(AspectRatio);
	return cam_;
}

Ogre::Entity * GestorRecursos::createPlane(Ogre::SceneManager * scnMgn, std::string name, std::string MaterialName, Ogre::Real width, Ogre::Real height, int Xsegments, int Ysegments, Ogre::SceneNode* FatherNode, std::string groupName)
{
	Ogre::Entity* plane;
	Ogre::MeshManager::getSingleton().createPlane(name, groupName, Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), width, height,
		Xsegments, Ysegments, true, 1, 1.0, 1.0, Ogre::Vector3::NEGATIVE_UNIT_Z);
	plane = scnMgn->createEntity(name);
	plane->setMaterialName(MaterialName);
	FatherNode->attachObject(plane);
	return plane;
}

TerrainCreator * GestorRecursos::createTerrain(Ogre::SceneManager * scnMgn, Ogre::Light * light, std::string terrainFile)
{
	TerrainCreator* terrainCreator_ = new TerrainCreator(scnMgn, light, terrainFile);
	return terrainCreator_;
}


GestorRecursos::GestorRecursos()
{

}

GestorRecursos::~GestorRecursos()
{
	instance_.release();
}

GestorRecursos * GestorRecursos::instance()
{

	if (instance_.get() == nullptr)
		instance_.reset(new GestorRecursos());

	return instance_.get();
}

void GestorRecursos::initializeResources()
{
	Ogre::ConfigFile cf;
	
		Ogre::FileSystemLayer* mFSLayer = OGRE_NEW Ogre::FileSystemLayer("cfLayerSystem");
		//Este metodo ya agrega '_d' si se compila en debug
		Ogre::String resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");

		std::string jsonPath;
	
		if (Ogre::FileSystemLayer::fileExists(resourcesPath))
			cf.load(resourcesPath);
	
		else
			throw::std::invalid_argument("Archivo resources.cfg no encontrado");
	
		Ogre::String sec, type, arch;
	
		// Recorre todos los grupos de recursos definidos en el archivo
		Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
	
		for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci)
		{
			sec = seci->first;
	
			const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
			Ogre::ConfigFile::SettingsMultiMap::const_iterator i;
	
			// Recorre todos los path
			for (i = settings.begin(); i != settings.end(); i++)
			{
				type = i->first;
				std::string auxPath = resourcesPath;
				auxPath.erase(auxPath.find_last_of("\\") + 1, auxPath.size() - 1);
				jsonPath = auxPath;
				arch = auxPath + Ogre::FileSystemLayer::resolveBundlePath(i->second);
	
				//Va agregando las ubicaciones definidas en el cfg
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
			}
		}
	
		Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	
		OGRE_DELETE mFSLayer;

		loadJsonsFiles(jsonPath);
}

json GestorRecursos::getJsonByKey(const std::string & key)
{
	std::map<std::string, json>::iterator it = jsonMap.find(key);
	
		//Si el puntero devuelve end() no ha encontrado ese archivo
		if (it != jsonMap.end()) return (*it).second;
		else return nullptr; 
}

void GestorRecursos::loadJsonsFiles(const std::string resourcesPath)
{
	//Se le añade al path exes la carpeta Assets\\jsons
	std::string filePath = resourcesPath + FOLDER_PATH;
	const char* filePathC = filePath.c_str();

	DIR *dir;
	struct dirent *ent;

	/*Se busca todos los archivos que existen el el directorio filePathPc*/
	if ((dir = opendir(filePathC)) != NULL) {

		while ((ent = readdir(dir)) != NULL) {
			//No se procesa el dir actual ni el padre
			if ((strcmp(ent->d_name, ".") == 1) && (strcmp(ent->d_name, "..") == 1)) {

				//Para los demas se abren, se leen y se pasan al tipo json
				std::fstream fStream;
				fStream.open(filePath + ent->d_name);
				loadJson(filePath + ent->d_name, ent->d_name);
				fStream.close();
			}
		}
		closedir(dir);
	}
}

void GestorRecursos::loadJson(const std::string & streamFilePath, const std::string & fileName)
{
	std::fstream stream_(streamFilePath);
	json j;
	stream_ >> j;
	//Se inserta los json que se van encontrando en el dir al diccionario
	jsonMap.insert(std::pair<std::string, json>(fileName, j));
}


