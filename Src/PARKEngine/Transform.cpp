#include "Transform.h"

Transform::Transform():position_(Vector3(0,0,0)), rotation_(Ogre::Quaternion::IDENTITY), scale_(Vector3(1,1,1))
{
	updateAxis();
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

	if (file.contains("scale"))
	{
		json scale = file["scale"];
		scale_.x = scale["x"];
		scale_.y = scale["y"];
		scale_.z = scale["z"];
	}
	updateAxis();
}

void Transform::translate(Vector3 incr)
{
	position_ += incr;
}

void Transform::rotate(Vector3 axis, float degrees)
{
	//Quaternions are fun
	//Pasamos a radianes
	Ogre::Radian radianAngle = Ogre::Radian(Ogre::Degree(degrees));

	//Obtenemos el cutarnión que simboliza esa transformación
	Ogre::Quaternion q;
	q.FromAngleAxis(radianAngle, axis);

	//Multiplicamos el cuaternión por la rotación
	rotation_ = rotation_ * q;
		
	//Normalizamos el cuaternión
	rotation_.normalise();

	//Update axis
	updateAxis();
}

void Transform::scale(Vector3 factor)
{
	scale_ *= factor;
}

void Transform::updateAxis()
{
	forward_ = getRotation() * Vector3::NEGATIVE_UNIT_Z;
	forward_.normalise();

	right_ = getRotation() * Vector3::NEGATIVE_UNIT_X;
	right_.normalise();

	up_ = getRotation() * Vector3::NEGATIVE_UNIT_Y;
	up_.normalise();
}



Transform::~Transform()
{
}

