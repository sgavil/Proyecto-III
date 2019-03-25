#include "InputManager.h"

std::unique_ptr<InputManager> InputManager::instance_;

InputManager * InputManager::instance()
{
	//Devuelve la instancia si exise, si no crea una nueva
	if (instance_.get() == nullptr)
		instance_.reset(new InputManager());

	return instance_.get();
}

InputManager::InputManager()
{
	unsigned long hWnd = OgreSystem::instance()->gethWnd();
	inputManager_ = OIS::InputManager::createInputSystem(hWnd);
	mouse_ = static_cast<OIS::Mouse*>(inputManager_->createInputObject(OIS::OISMouse, false));
	keyboard_ = static_cast<OIS::Keyboard*>(inputManager_->createInputObject(OIS::OISKeyboard, false));
}


InputManager::~InputManager()
{
}



Event InputManager::CheckInput()
{
	Event evento;
	keyboard_->capture();
	mouse_->capture();
	evento.keyboard_ = keyboard_;
	evento.mouse_ = mouse_;
	return evento;
}

void InputManager::attacheCameraToMouse(Ogre::SceneNode * cam)
{
	const OIS::MouseState& lMouseState = mouse_->getMouseState();

	float lMouseX = float(lMouseState.X.rel) / float(OgreSystem::instance()->getWindow()->getWidth());
	float lMouseY = float(lMouseState.Y.rel) / float(OgreSystem::instance()->getWindow()->getHeight());
	float lRotCoeff = -5.0f;
	Ogre::Radian lAngleX(lMouseX * lRotCoeff);
	Ogre::Radian lAngleY(lMouseY * lRotCoeff);

	// If the 'player' don't make loopings, 'yaw in world' + 'pitch in local' is often enough for a camera controler.
	cam->yaw(lAngleX, Ogre::Node::TS_WORLD);
	cam->pitch(lAngleY, Ogre::Node::TS_LOCAL);

}

