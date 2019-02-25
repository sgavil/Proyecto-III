#include "initOgreApplication.h"
#include "Scenes/SceneManager.h"

void testScenas()
{
	SceneManager* sceneManager = SceneManager::instance();

	MainMenuState* mainMenu = new MainMenuState();
	sceneManager->addState(MAIN_MENU, mainMenu);
	sceneManager->changeState(PLAY);

	while (true)
	{
		sceneManager->currentState()->update(1);
		sceneManager->currentState()->render(1);
		sceneManager->currentState()->handleInput();
	}
}

initOgreApplication::initOgreApplication(Ogre::Root *root) : root_(root)
{	
	root->setRenderSystem(*(root->getAvailableRenderers().begin()));
	root->initialise(false);

	sceneMgr_ = root_->createSceneManager();
	mFSLayer = new Ogre::FileSystemLayer(APP_NAME);

	initializeResources();
	initWindow();

	
}


initOgreApplication::~initOgreApplication()
{
	delete sceneMgr_;
	delete window_;
	delete camera_;
	delete viewport_;
	delete mFSLayer;
}

Ogre::SceneManager * initOgreApplication::getSceneManager()
{
	return sceneMgr_;
}

void initOgreApplication::initWindow()
{
	window_ = root_->createRenderWindow(APP_NAME, WINDOW_WIDTH, WINDOW_HEIGHT, false);
	window_->setActive(true);
	window_->setAutoUpdated(true);
	window_->setDeactivateOnFocusChange(false);

	sceneMgr_->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

	light_ = sceneMgr_->createLight("prueba");
	lightNode_ = sceneMgr_->getRootSceneNode()->createChildSceneNode();
	lightNode_->attachObject(light_);

	lightNode_->setPosition(20, 80, 50);

	camNode_ = sceneMgr_->getRootSceneNode()->createChildSceneNode();

	//AQUI ESTA EL FALLO, AL HACERLO DE LA MANERA DESCOMENTADA VA BIEN PERO SI LLAMO 
	//AL METODO DE LA LIBRERIA ABAJO COMENTADO Y COMENTO LO QUE HACE AHORA DA ERROR 
	//DE LINKADO
	//____________________________________________________________
	
	
	//DESCOMENTAR ESTO PARA PROBAR Y COMENTAR LO DE DEBAJO

	camera_ = GestorRecursos::createCamera(sceneMgr_, "cam", camNode_, 5, 50000, true);
	camNode_->setPosition(0, 0, 140);
	viewport_ = window_->addViewport(camera_);
	viewport_->setClearEveryFrame(true);

	/*camera_ = sceneMgr_->createCamera("cam");
	camera_->setNearClipDistance(5);
	camera_->setFarClipDistance(50000);
	camera_->setAutoAspectRatio(true);
	camNode_->attachObject(camera_);
	camNode_->setPosition(0, 0, 300);
	camNode_->rotate(Ogre::Vector3::NEGATIVE_UNIT_X, Ogre::Degree(20));
	viewport_ = window_->addViewport(camera_);
	viewport_->setClearEveryFrame(true);
	//______________________________________________________________*/

	plane_.d = 1000;
	plane_.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	sceneMgr_->setSkyPlane(
		true, plane_, "SkyBox", 1500, 50, true, 1.5, 150, 150);

	Ogre::MeshManager::getSingleton().createPlane("Plano", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 1000, 500,
		100, 50, true, 1, 1.0, 1.0, Ogre::Vector3::NEGATIVE_UNIT_Z);
	suelo_ = sceneMgr_->createEntity("Plano");
	suelo_->setMaterialName("Tierra");
	sueloNodo_ = sceneMgr_->getRootSceneNode()->createChildSceneNode();
	sueloNodo_->attachObject(suelo_);
	sueloNodo_->setPosition(0, -60, 0);

	ogreEntity = sceneMgr_->createEntity("ogrehead.mesh");
	ogreNode_ = sceneMgr_->getRootSceneNode()->createChildSceneNode();
	ogreNode_->attachObject(ogreEntity);
	ogreNode_->setPosition(0, -30, 0);


	//testScenas();

	root_->startRendering();
}

void initOgreApplication::initializeResources()
{
	Ogre::ConfigFile cf;

	//Este metodo ya agrega '_d' si se compila en debug
	Ogre::String resourcesPath = mFSLayer->getConfigFilePath("resources.cfg"); 

	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
	{
		cf.load(resourcesPath);
	}
	else
	{
		throw::std::invalid_argument("Archivo resources.cfg no encontrado");
	}

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
			arch = auxPath + Ogre::FileSystemLayer::resolveBundlePath(i->second);

			//Va agregando las ubicaciones definidas en el cfg
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec); 		
		}
	}

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Ogre::FileInfoListPtr resources = Ogre::ResourceGroupManager::getSingleton().listResourceFileInfo("General");
	Ogre::Log log_("ResourcesGeneral.log");
	for (unsigned int i = 0; i < (*resources).size(); i++)
		log_.logMessage((*resources)[i].filename);
	
}

void initOgreApplication::defineTerrain(long x, long y)
{
}

void initOgreApplication::initBlendMaps(Ogre::Terrain * terrain)
{
}

void initOgreApplication::configureTerrainDefaults(Ogre::Light * light)
{
}

void initOgreApplication::getTerrainImage(bool flipX, bool flipY, Ogre::Image & img)
{
}
