#include "FirstPersonCamera.h"
#include "PARKEngine/PARKEngine.h"
#include "Matrix/Matrix.h"
#include "ThirdPersonCamera.h"


FirstPersonCamera::FirstPersonCamera(): camTransform_(nullptr), camRigid_(nullptr), prevMouse_(0,0)
{
}


FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::start()
{
	//No se puede hacer en el start porque puede que la matriz no se haya creado toa
	cam_ = SceneManager::instance()->currentState()->getEntitiesWithComponent<Camera>()[0]->getComponent<Camera>();
	camTransform_ = cam_->getBrotherComponent<Transform>();
	camRigid_ = cam_->getBrotherComponent<Rigidbody>();
	setActive(false);
}

void FirstPersonCamera::load(json file)
{
}

void FirstPersonCamera::receive(Message * msg)
{
	switch (msg->mType_)
	{
	case FIRST_PERSON_CAMERA:
	{
		//Update position
		camTransform_->setPosition(Vector3(0, 20, 0));
		camTransform_->pitch(45);
		//Update rigidbody position
		camRigid_->setTransform(camTransform_);
		camRigid_->setActive(true);

		//Switch components
		getBrotherComponent<ThirdPersonCamera>()->setActive(false);
		setActive(true);
		break;
	}
	default:
		break;
	}
}

bool FirstPersonCamera::handleEvent(unsigned int time)
{
	//Standard increment (for camera transfomations)
	float stdIncr = ((float)time / 2);
	//Pillamos la info del ratón y de la ventana
	Vector2 mouse = { (float)InputManager::getSingletonPtr()->getMouse()->getMouseState().X.abs, (float)InputManager::getSingletonPtr()->getMouse()->getMouseState().Y.abs };
	Vector2 windowSize = { OgreManager::instance()->getWindowSize(0),  OgreManager::instance()->getWindowSize(1) };

	//Incremento de la posición
	Vector3 delta = { 0,0,0 };

	//Change camera perspective (Third / first person)
	if (InputManager::getSingletonPtr()->isKeyDown("ChangeCamera"))
	{
		send(new Message(MessageId::THIRD_PERSON_CAMERA));
		return true;
	}


	//First person
	else
	{
		//Movimiento en las 4 direcciones
		if (InputManager::getSingletonPtr()->isKeyDown("MoveForwards"))
			delta += camTransform_->forward() * stdIncr * 0.5;
		else if (InputManager::getSingletonPtr()->isKeyDown("MoveBack"))
			delta += camTransform_->forward() * stdIncr * -0.5;
		if (InputManager::getSingletonPtr()->isKeyDown("MoveLeft"))
			delta += camTransform_->right() * stdIncr * -0.5;
		else if (InputManager::getSingletonPtr()->isKeyDown("MoveRight"))
			delta += camTransform_->right() * stdIncr * 0.5;

		//Salto
		if (InputManager::getSingletonPtr()->isKeyDown("Jump"))
			camRigid_->addForce(Vector3(0, 200, 0));

		//Rotaciones de la cámara 
		//Izquierda/derecha
		if (mouse.x < prevMouse_.x)
			camTransform_->yaw(prevMouse_.x - mouse.x);
		else if(mouse.x > prevMouse_.x)
			camTransform_->yaw(mouse.x - prevMouse_.x);
			
	}	

	//Move the camera
	if (delta.length() != 0)
		camRigid_->setPosition(camTransform_->getPosition() + delta);

	prevMouse_ = mouse;

	return false;
}