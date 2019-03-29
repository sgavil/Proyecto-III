#pragma once
#include <string>

class OgreManager;
class SceneManager;
class AudioManager;
class PhysicsManager;
class InputManager;


class Game {
public:
	Game(std::string basicConfig);
	~Game();

	void start();
	void run();
private:
	PhysicsManager* physSyst_;
	SceneManager* ScnMng_;
	OgreManager* ogreSyst_;
	AudioManager* audioSrc_;
	InputManager* inputManager_;

	bool exit;
};