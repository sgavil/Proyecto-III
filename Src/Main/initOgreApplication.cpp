#include "initOgreApplication.h"
#include "Scenes/SceneManager.h"

// Bootstrap CEGUI::System with an OgreRenderer object that uses the
// default Ogre rendering window as the default output surface, an Ogre based
// ResourceProvider, and an Ogre based ImageCodec.
   //CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem();

initOgreApplication::initOgreApplication(Ogre::Root *root, std::string initFileJson) : root_(root)
{	
	root->setRenderSystem(*(root->getAvailableRenderers().begin()));
	root->initialise(false);

	GestorRecursos::initializeResources();

	initFile = JsonManager::instance()->getJsonByKey(initFileJson);

	sceneMgr_ = root_->createSceneManager();

	initWindow();		

	//CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem();
}


initOgreApplication::~initOgreApplication()
{
	/*delete light_;
	delete window_;*/
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

	light_ = sceneMgr_->createLight("TestLight");
	light_->setType(Ogre::Light::LT_DIRECTIONAL);
	light_->setDirection(lightdir);
	light_->setDiffuseColour(Ogre::ColourValue::White);
	light_->setSpecularColour(Ogre::ColourValue(240 / 255, 240 / 255, 188 / 255));

	plane_.d = 1000;
	plane_.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	sceneMgr_->setSkyPlane(
		true, plane_, "SkyBox", 1500, 50, true, 1.5, 150, 150);
}
