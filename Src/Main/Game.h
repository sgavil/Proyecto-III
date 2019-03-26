#pragma once
#include <OgreStringVector.h>
#include <Arquitectura/Entity.h>
#include <string>

class OgreSystem;
class SceneManager;
class AudioSource;
class physicSystem;
class InputManager;


class Game {
public:
	Game(std::string basicConfig);
	~Game();

	void start();
	void run();
private:
	physicSystem* physSyst_;
	SceneManager* ScnMng_;
	OgreSystem* ogreSyst_;
	AudioSource* audioSrc_;
	InputManager* inputManager_;

	bool exit;
};