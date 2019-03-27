#include "OgreSystem.h"

//NUESTRO
#include <GestorRecursos/gestorDeRecursos.h>
#include "Scenes/SceneManager.h"

//CEGUI
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

//OIS
#include <OIS.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISInputManager.h>

#include "SDL.h"
//OGRE
#include <iostream>
#include <OgreLight.h>
#include <OgrePlane.h>
#include <OgreColourValue.h>
#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreRenderWindow.h>
#include <OgreLog.h>
#include <OgreConfigFile.h>



// Bootstrap CEGUI::System with an OgreRenderer object that uses the
// default Ogre rendering window as the default output surface, an Ogre based
// ResourceProvider, and an Ogre based ImageCodec.
   //CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem();

std::unique_ptr<OgreSystem> OgreSystem::instance_;




OgreSystem * OgreSystem::instance(std::string initFileJson)
{
	//Devuelve la instancia si exise, si no crea una nueva
	if (instance_.get() == nullptr)
		instance_.reset(new OgreSystem(initFileJson));

	return instance_.get();
}

OgreSystem * OgreSystem::instance()
{
	//Devuelve la instancia si exise, si no crea una nueva
	if (instance_.get() == nullptr)
		std::cout << "ERROR: OGRE INSTANCE HAS NOT BEEN INITIALISED PROPERLY" << std::endl;

	return instance_.get();
}


OgreSystem::OgreSystem(std::string initFileJson)
{	

#if _DEBUG
	root_ = new Ogre::Root("plugins_d.cfg");
#else 	
	root_ = new Ogre::Root("plugins.cfg");
#endif

	root_->setRenderSystem(*(root_->getAvailableRenderers().begin()));
	root_->initialise(false);

	GestorRecursos::instance()->initializeResources();

	initFile = GestorRecursos::instance()->getJsonByKey(initFileJson);

	sceneMgr_ = root_->createSceneManager();

	initWindow();		

	
	//ceguiInit();

	//Inicialización de ventana de SDL que se una a la de Ogre
	SDL_Init(SDL_INIT_EVERYTHING);
	hWnd = 0;
	window_->getCustomAttribute("WINDOW", &hWnd);
	SDL_CreateWindowFrom((void*)hWnd);
}

/*
void OgreSystem::ceguiInit() {
	//Carga de CEGUI y configurado automatico con elementos de OGRE
	CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(getWindow()));


}

*/

OgreSystem::~OgreSystem()
{
	CEGUI::System::destroy();
	
	if (root_ != nullptr)
		delete root_;

	instance_.release();
	
}

void OgreSystem::render(unsigned int deltaTime)
{
	root_->renderOneFrame((Ogre::Real)deltaTime / 1000);
}

Ogre::SceneManager * OgreSystem::getSM()
{
	return sceneMgr_;
}

void OgreSystem::initWindow()
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
#if _DEBUG
	sceneMgr_->showBoundingBoxes(true); //Para debuggear las aabb
#endif
}
