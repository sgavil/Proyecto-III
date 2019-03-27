#include "ResourceManager.h"

//CEGUI
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

//OGRE
#include <Arquitectura/OgreIncludes.h>

//NUESTRO
#include <Arquitectura/OgreSystem.h>



std::unique_ptr<ResourceManager> ResourceManager::instance_;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	instance_.release();
}

ResourceManager * ResourceManager::instance()
{

	if (instance_.get() == nullptr)
		instance_.reset(new ResourceManager());

	return instance_.get();
}

void ResourceManager::initializeResources()
{
	Ogre::ConfigFile cf;

	Ogre::FileSystemLayer* mFSLayer = OgreSystem::instance()->createFileSystemLayer("cfLayerSystem");
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
			OgreSystem::instance()->getResourceGroupManager()->addResourceLocation(arch, type, sec);
		}
	}

	OgreSystem::instance()->getTextureManager()->setDefaultNumMipmaps(5);

	OgreSystem::instance()->getResourceGroupManager()->initialiseAllResourceGroups();

	OgreSystem::instance()->deleteFileSystemLayer(mFSLayer);

	loadJsonsFiles(jsonPath);

}

void ResourceManager::ceguiInit() {
	//Carga de CEGUI y configurado automatico con elementos de OGRE
	CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(OgreSystem::instance()->getWindow()));
}

json ResourceManager::getJsonByKey(const std::string & key)
{
	std::map<std::string, json>::iterator it = jsonMap.find(key);

	//Si el puntero devuelve end() no ha encontrado ese archivo
	if (it != jsonMap.end()) return (*it).second;
	else return nullptr;
}

void ResourceManager::loadJsonsFiles(const std::string resourcesPath)
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

void ResourceManager::loadJson(const std::string & streamFilePath, const std::string & fileName)
{
	std::fstream stream_(streamFilePath);
	json j;
	stream_ >> j;
	//Se inserta los json que se van encontrando en el dir al diccionario
	jsonMap.insert(std::pair<std::string, json>(fileName, j));
}


