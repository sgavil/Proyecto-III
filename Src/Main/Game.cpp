#include "Game.h"

Game::Game(std::string basicConfig)
{
#if _DEBUG
	root = new Ogre::Root("plugins_d.cfg");
#else 	
	root = new Ogre::Root("plugins.cfg");
#endif

	initOgreApplication* Ogreinit = new initOgreApplication(root);
	ScnMng_ = SceneManager::instance();
}

Game::~Game()
{
}

void Game::start()
{
	MainMenuState* menu = new MainMenuState(); //DEBERA LEERSE DE JSON
	ScnMng_->addState(MAIN_MENU, menu);
	ScnMng_->changeState(PLAY);
	
	update(2);
}

void Game::update(int time)
{
	while (true) {
		ScnMng_->currentState()->update(time);
		root->renderOneFrame();
	}
}
