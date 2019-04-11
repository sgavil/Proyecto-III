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


	virtual void load(json file);

	virtual void start();

	virtual bool handleEvent(unsigned int time);

protected:
	//References to Camera's components
	Camera * cam_;
	Transform* camTransform_;

	//Moves the camera a certain increment
	virtual void moveCamera(Vector3 deltaPos);

	////Makes the camera orbit around its focus a certain degree amount
	virtual void orbit(float degrees);

	//To help restraint camera movement within the matrix
	float MIN_HEIGTH;
	float MAX_HEIGTH;
};

REGISTER_TYPE(CameraManager)