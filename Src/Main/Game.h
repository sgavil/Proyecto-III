#pragma once
#include <string>

class OgreSystem;
class SceneManager;
class AudioSource;
class PhysicSystem;
class InputManager;


class Game {
public:
	Game(std::string basicConfig);
	~Game();

	void start();
	void run();
private:
	PhysicSystem* physSyst_;
	SceneManager* ScnMng_;
	OgreSystem* ogreSyst_;
	AudioSource* audioSrc_;
	InputManager* inputManager_;

	bool exit;
};