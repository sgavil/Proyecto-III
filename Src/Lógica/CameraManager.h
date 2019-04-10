#pragma once
#include "PARKEngine/Component.h"

class Camera;
class Transform;
class Matrix;

class CameraManager : public Component
{
public:
	CameraManager();
	~CameraManager();

	virtual void start();

	virtual void setup(Matrix* matrix);

	virtual bool handleEvent(unsigned int time);

protected:
	//References to Camera's components
	Camera * cam_;
	Transform* camTransform_;

	bool rotated_;

	//Moves the camera a certain increment
	virtual void moveCamera(Vector3 deltaPos);

	//Rotates around a certain point
	virtual void rotateAround(Vector3 center, float degrees);

	//To help restraint camera movement within the matrix
	Vector2 minCorner;
	Vector2 maxCorner;
	const int MIN_HEIGTH = 50;
	const int MAX_HEIGTH = 1000;
	const int OUT_OFFSET = 100;
};

REGISTER_TYPE(CameraManager)