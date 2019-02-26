#include "initOgreApplication.h"
#include <list>
#include <OgreResourceGroupManager.h>
#include <OgreStringVector.h>
#include "Arquitectura/Entity.h"
#include <Scenes/SceneManager.h>
#include <string>
#include <SDL.h>
#include <SDL_video.h>

using json = nlohmann::json;

class Game {
public:
	Game(std::string basicConfig);
	~Game();

	void start();
	void update(int time);
private:
	SceneManager* ScnMng_;
	Ogre::Root* root;
	initOgreApplication* Ogreinit_; //Información inicial de Ogre

	unsigned long hWnd; //Variable que toma la ventana de Ogre para aplicarla a la de SDL
};