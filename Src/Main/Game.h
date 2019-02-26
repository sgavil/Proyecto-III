#include "initOgreApplication.h"
#include <list>
#include <OgreResourceGroupManager.h>
#include <OgreStringVector.h>
#include "Arquitectura/Entity.h"
#include <Scenes/SceneManager.h>
#include <string>

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
};