#include "initOgreApplication.h"
#include "Scenes/SceneManager.h"

initOgreApplication::initOgreApplication(Ogre::Root *root, std::string initFileJson) : root_(root)
{	
	GestorRecursos::initGestor();

	root->setRenderSystem(*(root->getAvailableRenderers().begin()));
	root->initialise(false);

	GestorRecursos::initializeResources();

	initFile = GestorRecursos::jsonManager()->getJsonByKey(initFileJson);

	sceneMgr_ = root_->createSceneManager();
	
	initWindow();	
}


initOgreApplication::~initOgreApplication()
{
	delete sceneMgr_;
	delete window_;
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
