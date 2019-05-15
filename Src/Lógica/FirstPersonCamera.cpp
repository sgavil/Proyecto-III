#include "FirstPersonCamera.h"
#include "PARKEngine/PARKEngine.h"
#include "Matrix/Matrix.h"
#include "ThirdPersonCamera.h"


FirstPersonCamera::FirstPersonCamera(): camTransform_(nullptr), camRigid_(nullptr)
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
		//Restringimos el movimiento de la cámara
		camRigid_->setAngularFactor(Vector3(0, 1, 0));
		camRigid_->setLinearFactor(Vector3(1, 0, 1));

		//Update position
		camTransform_->setPosition(Vector3(0, 20, 0));
		camTransform_->pitch(45);
		//Update rigidbody position
		camRigid_->setTransform(camTransform_);
		camRigid_->setActive(true);

		//Hide cursor
		HUDManager::instance()->hideMouseCursor();
		
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
	Vector2 mouseAbs = { (float)InputManager::getSingletonPtr()->getMouse()->getMouseState().X.abs, (float)InputManager::getSingletonPtr()->getMouse()->getMouseState().Y.abs };
	Vector2 mouseRel = { (float)InputManager::getSingletonPtr()->getMouse()->getMouseState().X.rel, (float)InputManager::getSingletonPtr()->getMouse()->getMouseState().Y.rel };
	Vector2 windowSize = { OgreManager::instance()->getWindowSizeX(), OgreManager::instance()->getWindowSizeY() };

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
		Vector3 vel = { 0,0,0 };

		//Rotaciones con el ratón
		camTransform_->yaw(-mouseRel.x * 0.15f, REF_SYSTEM::GLOBAL);
		camRigid_->setTransform(camTransform_);

		//Movimiento en las 4 direcciones
		if (InputManager::getSingletonPtr()->isKeyDown("MoveForwards"))
			vel += (camTransform_->forward() * stdIncr * 20);
		else if (InputManager::getSingletonPtr()->isKeyDown("MoveBack"))
			vel += (camTransform_->forward() * stdIncr * -20);
		if (InputManager::getSingletonPtr()->isKeyDown("MoveLeft"))
			vel += (camTransform_->right() * stdIncr * -20);
		else if (InputManager::getSingletonPtr()->isKeyDown("MoveRight"))
		    vel += (camTransform_->right() * stdIncr * 20);

		////Salto
		//if (InputManager::getSingletonPtr()->isKeyDown("Jump"))
		//	camRigid_->setLinearVelocity(Vector3(0,stdIncr * 10,0));

		camRigid_->activate();
		camRigid_->setLinearVelocity(vel);
	}	
	
	camRigid_->setAngularVelocity(Vector3(0, 0, 0));
	return false;
}