#include "ResourceManager.h"

//CEGUI
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

//OGRE
#include <PARKEngine/OgreIncludes.h>

//NUESTRO
#include <PARKEngine/OgreManager.h>



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

	Ogre::FileSystemLayer* mFSLayer = OgreManager::instance()->createFileSystemLayer("cfLayerSystem");
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
			OgreManager::instance()->getResourceGroupManager()->addResourceLocation(arch, type, sec);
		}
	}

	OgreManager::instance()->getTextureManager()->setDefaultNumMipmaps(5);

	OgreManager::instance()->getResourceGroupManager()->initialiseAllResourceGroups();

	OgreManager::instance()->deleteFileSystemLayer(mFSLayer);

	loadJsonsFiles(jsonPath);

}

void ResourceManager::ceguiInit() {
	//Carga de CEGUI y configurado automatico con elementos de OGRE
	CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(OgreManager::instance()->getWindow()));

	//Carga de cosas
	// create (load) the TaharezLook scheme file
	// (this auto-loads the TaharezLook looknfeel and imageset files)
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

	// create (load) a font.
	// The first font loaded automatically becomes the default font, but note
	// that the scheme might have already loaded a font, so there may already
	// be a default set - if we want the "DejaVuSans-10" font to definitely
	// be the default, we should set the default explicitly afterwards.
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setImage("TaharezLook/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip");

	
	///////////////////////////////
	// ARRANCANDO INTERFAZ
	//	- Existen dos formas de hacerlo: Programando la interfaz directamente en c++ o cargandola completa de un archivo xml (layout)
	///////////////////////////////

	//////////////////////////////
	// USANDO C++
	//////////////////////////////

	//Crear ventana Invisible sobre la que construir el interfaz
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();		// Obtenemos la ventana de renderizado
	CEGUI::Window* myRoot = wmgr.createWindow("DefaultWindow", "root");		// Creamos una ventana de interfaz con parametros (Tipo ventana definida en Scheme activo, nombre asignado a la ventana)
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot); // Establece que sets de GUI se muestra en el contexto actual, puede cambiarse de uno a otro.

	//Hasta este punto ya se ha creado la ventana invisible sobre la que pondremos los widgets que formaran el menu
	//Vamos a crear elementos sobre esa ventana invisible
	CEGUI::FrameWindow* fWnd = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow("TaharezLook/FrameWindow", "testWindow"));
	myRoot->addChild(fWnd);
	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition(CEGUI::UVector2(CEGUI::UDim(0.75f, 0.0f), CEGUI::UDim(0.75f, 0.0f)));
	// set size to be half the size of the parent
	//fWnd->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.5f, 0.0f)));
	//fWnd->setMaxSize(CEGUI::USize(CEGUI::UDim(1.0, 0), CEGUI::UDim(1,0)));
	//fWnd->setWidth(CEGUI::UDim(1, 0));
	//fWnd->setHeight(CEGUI::UDim(1, 0));
	fWnd->setText("LePark!");
	// ¿Este elemento parece que no deja jugar con el tamaño? al menos no se como hacerlo. Los metodos que funcionan en el boton no van aqui.
	
	//Vamos a meter un boton
	CEGUI::PushButton* btn = static_cast<CEGUI::PushButton*>(wmgr.createWindow("TaharezLook/Button", "testButton"));
	myRoot->addChild(btn);
	btn->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.25f, 0.0f)));
	btn->setText("BOTONACO");
	//btn->setHeight(CEGUI::UDim(0.1, 0));

	//PARA ACCEDER A WIDGETS SE PUEDE HACER MEDIANTE CEGUI::WINDOW::getChild("ruta en el arbol de widgets omitiendo el root") p.ej: getChild(testWindow)
	// root --|-> testWindow -> myButton			se pueden buscar con getChild(testWindow), getChild(testWindow/myButton), getChild(Button2)
	//		  |-> Button2 


	////////////////////////////////////////////////////////////////////////////////////
	// USANDO ARCHIVOS XML .LAYOUT
	//  - Carga una archivo de REPOSITORIO/Dependencias/cegui-0.8.7/datafiles/layouts/
	//  - Dentro del archivo tiene que estar definidos todos los elementos de la interfaz a mostrar.
	////////////////////////////////////////////////////////////////////////////////////

	/*
	CEGUI::Window* myRoot2 = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("testWindow.layout");	// Cargamos un interfaz de usuario que ya hemos preparado en un archivo XML en los LAYOUTs
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot2);							// Establece que sets de GUI se muestra en el contexto actual, puede cambiarse de uno a otro.
	*/

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


