#pragma once
#include "Component.h"
#include <GestorRecursos/gestorDeRecursos.h>
#include <OgreEntity.h>
#include <OgreRenderWindow.h>
#include <SDL_video.h>
#include <iostream>
#include "OgreSystem.h"
#include "Transform.h"

class Camera : public Component
{
public:
	Camera();
	~Camera();

	virtual void start();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(SDL_Event* e, unsigned int time);
	virtual void receive(Message* msg) {};

	Ogre::SceneNode* camNode_;
	Ogre::Camera *camera_;
	Ogre::Viewport *viewport_;

	Transform* transform_;
};