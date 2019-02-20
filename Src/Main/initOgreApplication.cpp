#include "initOgreApplication.h"



initOgreApplication::initOgreApplication(Ogre::Root *root) : root_(root)
{
#ifdef _DEBUG
	root->loadPlugin("RenderSystem_GL_d");
	root->loadPlugin("Codec_STBI_d");
#else
	root->loadPlugin("RenderSystem_GL");
	root->loadPlugin("Codec_STBI");
#endif
	
	root->setRenderSystem(*(root->getAvailableRenderers().begin()));
	root->initialise(false);

	sceneMgr_ = root_->createSceneManager();
	mFSLayer = new Ogre::FileSystemLayer(APP_NAME);

	initWindow();
	initializeResources();
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

	camera_ = sceneMgr_->createCamera("cam");
	viewport_ = window_->addViewport(camera_);
	viewport_->setClearEveryFrame(true);
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
			arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);

			//Va agregando las ubicaciones definidas en el cfg
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec); 		
		}
	}

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Ogre::FileInfoListPtr resources = Ogre::ResourceGroupManager::getSingleton().listResourceFileInfo("General");
	Ogre::Log log_("log_");
	for (unsigned int i = 0; i < (*resources).size(); i++)
		log_.logMessage((*resources)[i].filename);
	
}
