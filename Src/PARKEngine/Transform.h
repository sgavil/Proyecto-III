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
	void setRotation(Ogre::Quaternion rotation) { this->rotation_ = rotation; updateAxis(); };
	//Scale setter
	void setScale(Vector3 scale) { this->scale_ = scale; };

	//TRANSFORMATIONS
	//Translate the component given a certain increment
	void translate(Vector3 incr);
	//Rotate the component around a certain axis
	void rotate(Vector3 axis, float degrees);
	//Multiplies the component scale for a given factor
	void scale(Vector3 factor);

	//LOCAL AXIS
	//Returns forward vector
	Vector3 forward() { return forward_; };
	//Returns right vector
	Vector3 right() { return right_; };
	//Returns up vector
	Vector3 up() { return up_; };




protected:
	//Position
	Vector3 position_;
	//Orientation (x,y,z,w)
	Ogre::Quaternion rotation_;
	//Scale
	Vector3 scale_;

	//LOCAL AXIS
	//Forward
	Vector3 forward_;
	//Right
	Vector3 right_;
	//Up
	Vector3 up_;

	//Updates axis
	void updateAxis();

};

REGISTER_TYPE(Transform)