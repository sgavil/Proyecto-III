#pragma once
#include "PARKEngine/Component.h"
#include <vector>

class Camera;
class Transform;
class Matrix;

struct CameraDirection {
	int id;
	float degrees;
	string direction;
};

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
	void slowRotation();
	CameraDirection dirCamera_;
	std::vector<CameraDirection> cameraDirections_;


	//To help restraint camera movement within the matrix
	float MIN_HEIGTH;
	float MAX_HEIGTH;

	//Fraction of the screen used to move the camera
	float borders_;

	bool rotating_;
};

REGISTER_TYPE(CameraManager)