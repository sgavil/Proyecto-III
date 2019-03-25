#pragma once
#include <Arquitectura/physicSystem.h>
#include <Scenes/SceneManager.h> 
#include <Arquitectura\OgreSystem.h>
#include <OgreStringVector.h>
#include <Arquitectura/Entity.h>
#include <string>
#include <SDL.h>
#include <SDL_video.h>
#include <AudioSource/AudioSource.h>
#include "vld.h"

#include <OISMouse.h>
#include <OISKeyboard.h>
#include <OISJoyStick.h>
#include <OISInputManager.h>

class Rigidbody;
class Game {
public:
	Game(std::string basicConfig);
	~Game();

	void start();
	void run();
private:
	physicSystem* physSyst_;
	SceneManager* ScnMng_;
	OgreSystem* ogreSyst_; //Informaci�n inicial de Ogre
	AudioSource* audioSrc_;
	Rigidbody* floorRigidbody;

	bool exit;
};