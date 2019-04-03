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

void Transform::rotate(Vector3 axis, float degrees)
{
	Ogre::Degree degreeAngle = Ogre::Degree(degrees);
	Ogre::Radian radianAngle = Ogre::Radian(degreeAngle);
	Ogre::Quaternion q;
	q.FromAngleAxis(radianAngle, axis);
	rotation_ = rotation_ * q;
		
	// Normalise quaternion to avoid drift
	rotation_.normalise();
}

void Transform::scale(Vector3 incr)
{
	scale_ *= incr;
}

Transform::~Transform()
{
}


//CÓDIGO DE ROTACIONES DE NODOS EN OGRE
//void Node::rotate(const Vector3& axis, const Radian& angle, TransformSpace relativeTo)
//{
//	Quaternion q;
//	q.FromAngleAxis(angle, axis);
//	rotate(q, relativeTo);
//}
//
////-----------------------------------------------------------------------
//void Node::rotate(const Quaternion& q, TransformSpace relativeTo)
//{
//	switch (relativeTo)
//	{
//	case TS_PARENT:
//		// Rotations are normally relative to local axes, transform up
//		mOrientation = q * mOrientation;
//		break;
//	case TS_WORLD:
//		// Rotations are normally relative to local axes, transform up
//		mOrientation = mOrientation * _getDerivedOrientation().Inverse()
//			* q * _getDerivedOrientation();
//		break;
//	case TS_LOCAL:
//		// Note the order of the mult, i.e. q comes after
//		mOrientation = mOrientation * q;
//		break;
//	}
//
//	// Normalise quaternion to avoid drift
//	mOrientation.normalise();
//
//	needUpdate();
//}