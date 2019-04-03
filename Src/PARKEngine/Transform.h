#pragma once
#include "Component.h"

class Transform : public Component
{
public:

	Transform();
	Transform(Vector3 position, Ogre::Quaternion rotation = Ogre::Quaternion::IDENTITY, Vector3 scale = Vector3(1,1,1));

	~Transform();

	virtual void load(json file);

	//GETTERS
	//Position getter
	Vector3 getPosition() { return position_; };
	//Rotation getter
	Ogre::Quaternion getRotation() { return rotation_; };
	//Scale getter
	Vector3 getScale() { return scale_; };


	//SETTERS
	//Position setter
	void setPosition(Vector3 pos) { this->position_ = pos; };
	//Rotation setter
	void setRotation(Ogre::Quaternion rotation) { this->rotation_ = rotation; };
	//Scale setter
	void setScale(Vector3 scale) { this->scale_ = scale; };

	//TRANSFORMATIONS
	//Translate the component given a certain increment
	void translate(Vector3 incr);
	//Rotate the component around a certain axis
	void rotate(Vector3 axis, float degrees);
	//Multiplies the component scale
	void scale(Vector3 incr);

protected:
	Vector3 position_;
	Ogre::Quaternion rotation_;
	Vector3 scale_;

	//void rotate(const Quaternion& q, TransformSpace relativeTo);
};

REGISTER_TYPE(Transform)