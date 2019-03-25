#pragma once
#include <OIS.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISInputManager.h>

#include "OgreSystem.h"
#include <OgreCamera.h>

struct Event {
	OIS::Mouse* mouse_;
	OIS::Keyboard* keyboard_;
};

class InputManager
{
public:

	//"Constructora" de la instancia
	static InputManager* instance();

private:
	InputManager();
public:
	~InputManager();
	//GETTERS
	OIS::Mouse* getMouse() { return mouse_; }
	OIS::Keyboard* getKeyboard() { return keyboard_; }

	//PARA COMPROBAR SI SE HA REALIZADO ALGUNA PULSACION DE INPUT
	Event CheckInput();

	//ESTE METODO APLICA A LA CAMARA QUE SE PIDE
	void attacheCameraToMouse(Ogre::SceneNode * cam);

private:
	OIS::Mouse* mouse_;
	OIS::Keyboard* keyboard_;
	OIS::InputManager* inputManager_;

	static std::unique_ptr<InputManager> instance_;
};

