#pragma once
#include "Component.h"

class Transform : public Component
{
public:

	Transform();
	Transform(Vector3 position, Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY, Vector3 scale = Vector3(1,1,1));

	~Transform();

	virtual void load(json file);

	//Position getter
	Vector3 getPosition() { return position_; };
	//Position setter
	void setPosition(Vector3 pos) { this->position_ = pos; };

	//Orientation getter
	Ogre::Quaternion getOrientation() { return orientation_; };
	//Orientation setter
	void setOrientation(Ogre::Quaternion orientation) { this->orientation_ = orientation; };
	
	//Scale getter
	Vector3 getScale() { return scale_; };
	//Scale setter
	void setScale(Vector3 scale) { this->scale_ = scale; };

protected:
	Vector3 position_;
	Ogre::Quaternion orientation_;
	Vector3 scale_;
};

REGISTER_TYPE(Transform)