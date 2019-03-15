#pragma once
#include "Component.h""
#include <OgreSceneNode.h>

class Transform : public Component
{
public:

	//Crea una entidad renderizable a partir del nombre de su malla y una posición inicial
	Transform();

	~Transform();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(SDL_Event* e, unsigned int time);
	virtual void receive(Message* msg) {};

protected:
	Ogre::Vector3 position_;
	Ogre::Vector3 rotation_;
	Ogre::Vector3 scale_;
};

