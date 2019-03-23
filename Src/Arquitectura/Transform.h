#pragma once
#include "Component.h"
#include <OgreSceneNode.h>

class Transform : public Component
{
public:

	//Crea una entidad renderizable a partir del nombre de su malla y una posición inicial
	Transform();
	Transform(Ogre::Vector3 position, Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY, Ogre::Vector3 scale = Ogre::Vector3(1,1,1));

	~Transform();

	void load(json file);

	//Métodos principales
	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(SDL_Event* e, unsigned int time);
	virtual void receive(Message* msg) {};

	//Position getter
	Ogre::Vector3 getPosition() { return position_; };
	//Position setter
	void setPosition(Ogre::Vector3 pos) { this->position_ = pos; };

	//Orientation getter
	Ogre::Quaternion getOrientation() { return orientation_; };
	//Orientation setter
	void setOrientation(Ogre::Quaternion orientation) { this->orientation_ = orientation; };
	
	//Scale getter
	Ogre::Vector3 getScale() { return scale_; };
	//Scale setter
	void setScale(Ogre::Vector3 scale) { this->scale_ = scale; };

protected:
	Ogre::Vector3 position_;
	Ogre::Quaternion orientation_;
	Ogre::Vector3 scale_;
};

REGISTER_TYPE(Transform)