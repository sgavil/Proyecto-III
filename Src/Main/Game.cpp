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


}

Game::~Game()
{
	delete ScnMng_;
	delete root;
}

void Game::start()
{
	PlayState* playstate = new PlayState(Ogreinit_->getSceneManager(), Ogreinit_->getWindow()); 
	ScnMng_->addState(PLAY, playstate);
	ScnMng_->changeState(PLAY);
	
	update(SDL_GetTicks());
}

void Game::update(int time)
{
	while (true) {
		ScnMng_->currentState()->update(time);
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
