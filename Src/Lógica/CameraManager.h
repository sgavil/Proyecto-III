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

	virtual bool handleEvent(unsigned int time);

protected:
	Camera * cam_;
	Transform* camTransform_;
	Matrix* matrix_;

	bool rotated_;

	//Moves the camera a certain increment
	virtual void moveCamera(Vector3 deltaPos);

	virtual void rotateAround(Vector3 center, float degrees);
};

REGISTER_TYPE(CameraManager)