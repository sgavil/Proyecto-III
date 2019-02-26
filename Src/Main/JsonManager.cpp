#include "JsonManager.h"

template<> JsonManager *Ogre::Singleton<JsonManager>::msSingleton = 0;

JsonManager *JsonManager::getSingletonPtr(void)
{
	return msSingleton;
}

JsonManager &JsonManager::getSingleton(void)
{
	assert(msSingleton);
	return(*msSingleton);
}

JsonManager::JsonManager()
{
	/*Se busca la ruta del resources.cfg para poder encontrar la ruta relativa de la carpeta Assets*/
	mFSLayer = new Ogre::FileSystemLayer("jsonManLayer");
	resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");
	Ogre::String auxPath = resourcesPath;

	//Se limpia el string
	resourcesPath.erase(resourcesPath.find_last_of("\\") + 1, resourcesPath.size() - 1);

	loadJsonFiles();
}

JsonManager::~JsonManager()
{
	delete mFSLayer;
}

void JsonManager::loadJsonFiles()
{
	//Se le añade al path exes la carpeta Assets\\jsons
	std::string filePath = resourcesPath + folderPath;
	const char* filePathC = filePath.c_str();

	DIR *dir;
	struct dirent *ent;
	
	/*Se busca todos los archivos que existen el el directorio filePathPc*/
	if ((dir = opendir(filePathC)) != NULL) {
		
		while ((ent = readdir(dir)) != NULL ) {
			//No se procesa el dir actual ni el padre
			if ((strcmp(ent->d_name,".") == 1) && (strcmp(ent->d_name, "..") == 1)) {

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

json JsonManager::getJsonByKey(const std::string &key)
{
	std::map<std::string,json>::iterator it = jsonMap.find(key);

	//Si el puntero devuelve end() no ha encontrado ese archivo
	if (it != jsonMap.end()) return (*it).second;
	else return nullptr; 
}

void JsonManager::loadJson(const std::string &streamFilePath, const std::string &fileName)
{
	std::fstream stream_(streamFilePath);
	json j;
	stream_ >> j;
	//Se inserta los json que se van encontrando en el dir al diccionario
	jsonMap.insert(std::pair<std::string, json>(fileName, j));
}



