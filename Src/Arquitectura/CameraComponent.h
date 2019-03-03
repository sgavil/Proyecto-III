#pragma once
#include "Component.h""
#include <GestorRecursos/gestorDeRecursos.h>
#include <OgreEntity.h>
#include <OgreRenderWindow.h>
#include <SDL.h>
#include <SDL_video.h>
#include <iostream>

class CameraComponent : public Component
{
public:
	CameraComponent(Ogre::SceneManager* scnMgn, Ogre::RenderWindow* wind);
	~CameraComponent();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual void handleEvent() {};
	virtual void receive(Message* msg) {};

	Ogre::SceneNode* camNode_;
	Ogre::Camera *camera_;
	Ogre::Viewport *viewport_;
};

