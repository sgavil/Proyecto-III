#include "Game.h"

Game::Game(std::string basicConfig)
{
#if _DEBUG
	root = new Ogre::Root("plugins_d.cfg");
#else 	
	root = new Ogre::Root("plugins.cfg");
#endif

	SDL_Init(SDL_INIT_EVENTS);

	//aqui se inicia el stream de lectura con el archivo de json de los valores iniciales de la ventana
	std::ifstream i(basicConfig);
	json initFile;
	i >> initFile;
	initOgreApplication* Ogreinit = new initOgreApplication(root, initFile);
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
