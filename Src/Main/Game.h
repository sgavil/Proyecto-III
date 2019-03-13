#pragma once
#include <Scenes/SceneManager.h> //Esto tiene que ir lo primero porque tiene physicSystem
#include "initOgreApplication.h"
#include <OgreStringVector.h>
//#include <Arquitectura/Entity.h>
#include <string>
#include <SDL.h>
#include <SDL_video.h>
#include <AudioSource/AudioSource.h>
#include "vld.h"

class RigidbodyComponent;
class Game {
public:
	Game(std::string basicConfig);
	~Game();

	void start();
	void run();
private:
	physicSystem* physSyst_;
	SceneManager* ScnMng_;
	Ogre::Root* root;
	initOgreApplication* Ogreinit_; //Información inicial de Ogre
	AudioSource* audioSrc_;
	RigidbodyComponent* floorRigidComp;

	unsigned long hWnd; //Variable que toma la ventana de Ogre para aplicarla a la de SDL
	bool exit;
};