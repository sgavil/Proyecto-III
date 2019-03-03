#include <map>
#include <string>
#include <fstream>
#include <OgreFileSystemLayer.h>
#include <dirent.h>
#include <OgreSingleton.h>
#include <jsonParser.hpp>

/*
Este manager se encarga de buscar todos los archivos json en la carpeta Assets\\jsons, los lee y los pasa a un archivo de tipo
json para despues agregarlos al diccionario jsonMap.

Se puede pedir los archvios a traves del manager utilizando la key correspondiente al nombre del fichero json

*/
using json = nlohmann::json;

class JsonManager : public Ogre::Singleton<JsonManager>
{
public:
	JsonManager();
	~JsonManager();
	void loadJsonFiles();

	json getJsonByKey(const std::string &key); //Devuelve el archivo json dado el nombre de archivo alojado en assets\jsons

	static JsonManager &getSingleton(void);
	static JsonManager *getSingletonPtr(void);
private:

	void loadJson(const std::string &streamFilePath,const std::string &fileName);

	Ogre::String resourcesPath;
	std::map<std::string, json> jsonMap;
	Ogre::FileSystemLayer* mFSLayer;

	const std::string folderPath = "Assets\\jsons\\";

};

