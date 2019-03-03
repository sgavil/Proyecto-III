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

initOgreApplication::initOgreApplication(Ogre::Root *root, std::string initFileJson) : root_(root)
{	
	GestorRecursos::initGestor();

	root->setRenderSystem(*(root->getAvailableRenderers().begin()));
	root->initialise(false);

	GestorRecursos::initializeResources();

	initFile = GestorRecursos::jsonManager()->getJsonByKey(initFileJson);
	mapsFile = GestorRecursos::jsonManager()->getJsonByKey("Maps.json");

	sceneMgr_ = root_->createSceneManager();
	

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
	window_ = root_->createRenderWindow(initFile["WindowName"], initFile["Width"], initFile["Height"], false);
	window_->setFullscreen(initFile["fullScreen"], initFile["Width"], initFile["Height"]);
	window_->setActive(true);
	window_->setAutoUpdated(true);
	window_->setDeactivateOnFocusChange(false);

	sceneMgr_->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

	Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
	lightdir.normalise();

	Ogre::Light* light = sceneMgr_->createLight("TestLight");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(lightdir);
	light->setDiffuseColour(Ogre::ColourValue::White);
	light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));

	camNode_ = sceneMgr_->getRootSceneNode()->createChildSceneNode();

	//AQUI ESTA EL FALLO, AL HACERLO DE LA MANERA DESCOMENTADA VA BIEN PERO SI LLAMO 
	//AL METODO DE LA LIBRERIA ABAJO COMENTADO Y COMENTO LO QUE HACE AHORA DA ERROR 
	//DE LINKADO
	//____________________________________________________________
	
	
	//DESCOMENTAR ESTO PARA PROBAR Y COMENTAR LO DE DEBAJO

	camera_ = GestorRecursos::createCamera(sceneMgr_, "cam", camNode_, 5, 50000, true);
	camNode_->setPosition(1683, 50, 2116);
	//camNode_->setPosition(0, 0, 140);
	camNode_->lookAt(Ogre::Vector3(1963, 50, 1660), Ogre::Node::TS_WORLD);
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

	/*Ogre::MeshManager::getSingleton().createPlane("Plano", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 1000, 500,
		100, 50, true, 1, 1.0, 1.0, Ogre::Vector3::NEGATIVE_UNIT_Z);
	suelo_ = sceneMgr_->createEntity("Plano");
	suelo_->setMaterialName("Tierra");
	sueloNodo_ = sceneMgr_->getRootSceneNode()->createChildSceneNode();
	sueloNodo_->attachObject(suelo_);
	sueloNodo_->setPosition(0, -60, 0);*/

	ogreEntity = sceneMgr_->createEntity("ogrehead.mesh");
	ogreNode_ = sceneMgr_->getRootSceneNode()->createChildSceneNode();
	ogreNode_->attachObject(ogreEntity);
	ogreNode_->setPosition(0, -30, 0);


	//testScenas();

	//Test del terreno
	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(
		sceneMgr_,
		Ogre::Terrain::ALIGN_X_Z,
		mapsFile["maps"][0]["terrainSize"], mapsFile["maps"][0]["worldSize"]);
	mTerrainGroup->setFilenameConvention(Ogre::String("terrain"), Ogre::String("dat"));
	mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

	configureTerrainDefaults(light);

	for (long x = 0; x <= 0; ++x)
		for (long y = 0; y <= 0; ++y)
			defineTerrain(x, y);

	mTerrainGroup->loadAllTerrains(true);

	if (mTerrainsImported)
	{
		Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();

		while (ti.hasMoreElements())
		{
			Ogre::Terrain* t = ti.getNext()->instance;
			initBlendMaps(t);
		}
	}

	mTerrainGroup->freeTemporaryResources();
}


void initOgreApplication::defineTerrain(long x, long y)
{
	Ogre::String filename = mTerrainGroup->generateFilename(x, y);
	
	bool exists = Ogre::ResourceGroupManager::getSingleton().resourceExists(
			mTerrainGroup->getResourceGroup(),
			filename);

	if (exists)
		mTerrainGroup->defineTerrain(x, y);
	else
	{
		Ogre::Image img;
		getTerrainImage(x % 2 != 0, y % 2 != 0, img);
		mTerrainGroup->defineTerrain(x, y, &img);

		mTerrainsImported = true;
	}
}

void initOgreApplication::initBlendMaps(Ogre::Terrain * terrain)
{
	Ogre::Real minHeight0 = mapsFile["maps"][0]["minHeight0"];
	Ogre::Real fadeDist0 = mapsFile["maps"][0]["fadeDist0"];
	Ogre::Real minHeight1 = mapsFile["maps"][0]["minHeight1"];
	Ogre::Real fadeDist1 = mapsFile["maps"][0]["fadeDist1"];

	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
	Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);

	float* pBlend0 = blendMap0->getBlendPointer();
	float* pBlend1 = blendMap1->getBlendPointer();

	for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
	{
		for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
		{
			Ogre::Real tx, ty;

			blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
			Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
			Ogre::Real val = (height - minHeight0) / fadeDist0;
			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
			*pBlend0++ = val;

			val = (height - minHeight1) / fadeDist1;
			val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
			*pBlend1++ = val;
		}
	}

	blendMap0->dirty();
	blendMap1->dirty();
	blendMap0->update();
	blendMap1->update();
}

void initOgreApplication::configureTerrainDefaults(Ogre::Light * light)
{
	mTerrainGlobals->setMaxPixelError(8);
	mTerrainGlobals->setCompositeMapDistance(3000);

	mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
	mTerrainGlobals->setCompositeMapAmbient(sceneMgr_->getAmbientLight());
	mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

	Ogre::Terrain::ImportData& importData = mTerrainGroup->getDefaultImportSettings();
	importData.terrainSize = mapsFile["maps"][0]["terrainSize"];
	importData.worldSize = mapsFile["maps"][0]["worldSize"];
	importData.inputScale = mapsFile["maps"][0]["inputScale"];
	importData.minBatchSize = mapsFile["maps"][0]["minBatchSize"];
	importData.maxBatchSize = mapsFile["maps"][0]["maxBatchSize"];

	importData.layerList.resize(mapsFile["maps"][0]["layerListSize"]);

	for (int i = 0; i < importData.layerList.size(); i++)
	{
		importData.layerList[i].worldSize = mapsFile["maps"][0]["layerWorldSizeList"][i];
		importData.layerList[i].textureNames.push_back(
			mapsFile["maps"][0]["diffuseSpecularTexturesNames"][i]);
		importData.layerList[i].textureNames.push_back(
			mapsFile["maps"][0]["normalHeightTexturesNames"][i]);
	}
}

void initOgreApplication::getTerrainImage(bool flipX, bool flipY, Ogre::Image & img)
{
	img.load(mapsFile["maps"][0]["terrainImage"], Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	if (flipX)
		img.flipAroundY();
	if (flipY)
		img.flipAroundX();
}