#include "Transform.h"

Transform::Transform():position_(Vector3(0,0,0)), orientation_(Ogre::Quaternion::IDENTITY), scale_(Vector3(1,1,1))
{
}

Transform::Transform(Vector3 position, Ogre::Quaternion orientation, Vector3 scale)
	:position_(position), orientation_(orientation), scale_(scale)
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

Transform::~Transform()
{
}