#include "CameraManager.h"
#include "PARKEngine/PARKEngine.h"
#include "Matrix/Matrix.h"


CameraManager::CameraManager(): camTransform_(nullptr), camRigid_(nullptr), rotating_(false), borders_(0), firstPerson_(false), prevMouse_(0,0)
{
}


CameraManager::~CameraManager()
{
}

void CameraManager::start()
{
	//No se puede hacer en el start porque puede que la matriz no se haya creado toa
	cam_ = SceneManager::instance()->currentState()->getEntitiesWithComponent<Camera>()[0]->getComponent<Camera>();
	camTransform_ = cam_->getBrotherComponent<Transform>();
	camRigid_ = cam_->getBrotherComponent<Rigidbody>();
	camTransform_->yaw(0, REF_SYSTEM::GLOBAL);
	camRigid_->setActive(false);
}

void CameraManager::load(json file)
{
	addParameter(MAX_HEIGTH, file["maxHeigth"]);
	addParameter(MIN_HEIGTH, file["minHeigth"]);
	addParameter(borders_, file["borders"]);
}


bool CameraManager::handleEvent(unsigned int time)
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
		firstPerson_ = !firstPerson_;
		Message* m;
		if(firstPerson_)
		{
			camTransform_->setPosition(Vector3(0, 20, 0));
			camTransform_->pitch(45);
			m = new Message(MessageId::FIRST_PERSON_CAMERA);
		}

		else
		{
			camTransform_->setPosition(Vector3(0, 500, 500));
			camTransform_->pitch(-45);
			m = new Message(MessageId::THIRD_PERSON_CAMERA);
		}
			
		//Update rigidbody position
		camRigid_->setTransform(camTransform_);
		camRigid_->setActive(firstPerson_);

		send(m);
	}

	//First person
	else if(firstPerson_)
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

	//Third person
	else
	{

		//ADELANTE/ATRÁS
		if (mouse.y < windowSize.y * borders_)
			delta += Vector3::UNIT_Y.crossProduct(camTransform_->right()) * stdIncr;
		else if (mouse.y > windowSize.y - windowSize.y * borders_)
			delta += Vector3::UNIT_Y.crossProduct(camTransform_->right()) * -stdIncr;

		//IZQUIERDA/DERECHA
		if (mouse.x < windowSize.x * borders_)
			delta += camTransform_->right() * -stdIncr;
		else if (mouse.x > windowSize.x - windowSize.x * borders_)
			delta += camTransform_->right() * stdIncr;

		//Rueda del ratón para hacer zoom (no se como se pone esto en el archivo del input porque no son teclas como tales)
		//ZOOM IN/OUT
		if (InputManager::getSingletonPtr()->getMouse()->getMouseState().Z.rel > 0)
			delta += camTransform_->forward() * stdIncr * 1.5; //TODO: poner un parámetro de sensibilidad

		else if (InputManager::getSingletonPtr()->getMouse()->getMouseState().Z.rel < 0)
			delta += camTransform_->forward() * stdIncr * -1.5;

		//ROTACIONES
		if (InputManager::getSingletonPtr()->isKeyDown("RotateLeft"))
			orbit(-90);
		else if (InputManager::getSingletonPtr()->isKeyDown("RotateRight"))
			orbit(90);
		else
			rotating_ = false;
	}

	//Move the camera
	if (delta.length() != 0)
		moveCamera(delta);

	prevMouse_ = mouse;

	return false;
}


void CameraManager::orbit(float degrees)
{
	if (!rotating_)
	{
		int index;
		index = (degrees > 0) ? 1 : -1;

		//Throw a ray
		Vector3 focus = OgreManager::instance()->raycast().second;
		Vector3 horizDistance = { focus.x - camTransform_->getPosition().x, 0 , focus.z - camTransform_->getPosition().z };
		//Rotate the camera
		camTransform_->yaw(degrees, REF_SYSTEM::GLOBAL);
		//Translate the camera getting the difference betwwen the 2 vectors
		camTransform_->translate(camTransform_->right() * index *horizDistance.length());
		camTransform_->translate(Vector3::UNIT_Y.crossProduct(camTransform_->right()) * -horizDistance.length());

		rotating_ = true;
	}
}

void CameraManager::moveCamera(Vector3 deltaPos)
{
	//Note that what we want to be inside the map isn't the camera itself, but the point 
	//which it is heading (the "focus"). Therefore, we make the calculus with this focus in mind
	//(except for the Y coordinate)

	//Move the camera towards the desired place and throw another ray
	

	if(firstPerson_)
	{
		camRigid_->setPosition(camTransform_->getPosition() + deltaPos);
	}
	else
	{
		camTransform_->translate(deltaPos);
		//If the ray is out of the matrix or we want to go too up/down
		float y = camTransform_->getPosition().y;
		if (OgreManager::instance()->raycast().first == nullptr || y > MAX_HEIGTH || y < MIN_HEIGTH)
			camTransform_->translate(-deltaPos);
	}
}