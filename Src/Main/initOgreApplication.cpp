#include "initOgreApplication.h"



initOgreApplication::initOgreApplication(Ogre::Root *root) : root_(root)
{
#ifdef _DEBUG
	root->loadPlugin("RenderSystem_GL_d");
#else
	root->loadPlugin("RenderSystem_GL");
#endif
	root->setRenderSystem(*(root->getAvailableRenderers().begin()));
	root->initialise(false);

	sceneMgr_ = root_->createSceneManager();

	initWindow();
}


initOgreApplication::~initOgreApplication()
{
	delete sceneMgr_;
	delete window_;
	delete camera_;
	delete viewport_;
}

void initOgreApplication::initWindow()
{
	window_ = root_->createRenderWindow("Theme Park", 800, 600, false);
	window_->setActive(true);
	window_->setAutoUpdated(true);
	window_->setDeactivateOnFocusChange(false);

	camera_ = sceneMgr_->createCamera("cam");
	viewport_ = window_->addViewport(camera_);
	viewport_->setClearEveryFrame(true);
}
