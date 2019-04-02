#include "Transform.h"

Transform::Transform():position_(Vector3(0,0,0)), rotation_(Ogre::Quaternion::IDENTITY), scale_(Vector3(1,1,1))
{
}

Transform::Transform(Vector3 position, Ogre::Quaternion rotation, Vector3 scale)
	:position_(position), rotation_(rotation), scale_(scale)
{
}

void Transform::load(json file)
{
	json pos = file["position"];
	position_.x = pos["x"];
	position_.y = pos["y"];
	position_.z = pos["z"];

	//json scale = file["scale"];
	//scale_.x = scale["x"];
	//scale_.y = scale["y"];
	//scale_.z = scale["z"];
}

void Transform::translate(Vector3 incr)
{
	position_ += incr;
}

void Transform::rotate(Vector3 axis, float angle)
{
	//TODO: ROTAR EL CUATERNION
}

void Transform::scale(Vector3 incr)
{
	scale_ *= incr;
}

Transform::~Transform()
{
}