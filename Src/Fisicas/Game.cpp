#include "Game.h"

Game::Game(std::string basicConfig)
{
#if _DEBUG
	root = new Ogre::Root("plugins_d.cfg");
#else 	
	root = new Ogre::Root("plugins.cfg");
#endif

	Ogreinit_ = new initOgreApplication(root, basicConfig);

	//Inicialización de ventana de SDL que se una a la de Ogre
	SDL_Init(SDL_INIT_EVERYTHING);
	hWnd = 0;
	Ogreinit_->getWindow()->getCustomAttribute("WINDOW", &hWnd);
	SDL_CreateWindowFrom((void*)hWnd);

	ScnMng_ = SceneManager::instance();

	//Físicas
	pSystem_ = physicSystem::instance();


}

Game::~Game()
{	
	delete ScnMng_;
	delete root;
	pSystem_->clenaupPhysics();
	delete pSystem_;
}

void Game::start()
{
	MainMenuState* menu = new MainMenuState(); //DEBERA LEERSE DE JSON
	ScnMng_->addState(MAIN_MENU, menu);
	ScnMng_->changeState(PLAY);

	//FISICAS
	pSystem_->initPhysics();
	
	update(2);
}

void Game::update(int time)
{
	while (true) {
		ScnMng_->currentState()->update(time);
		pSystem_->stepSimulation(); //FÍSICAS
		root->renderOneFrame();


		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				//EXIT = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
				if (event.key.keysym.sym == SDLK_UP)
				{
					std::cout << "Hola! Funciono" << std::endl;
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					
				}
			}
		}
	}
}
