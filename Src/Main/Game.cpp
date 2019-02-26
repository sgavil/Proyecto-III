#include "Game.h"

Game::Game(std::string basicConfig)
{
#if _DEBUG
	root = new Ogre::Root("plugins_d.cfg");
#else 	
	root = new Ogre::Root("plugins.cfg");
#endif

	//aqui se inicia el stream de lectura con el archivo de json de los valores iniciales de la ventana
	std::ifstream i(basicConfig);
	json initFile;
	i >> initFile;
	Ogreinit_ = new initOgreApplication(root, initFile);

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
