#include "CameraManager.h"
#include "PARKEngine/PARKEngine.h"
#include "Matrix/Matrix.h"


CameraManager::CameraManager():rotated_(false)
{
}


CameraManager::~CameraManager()
{
}

void CameraManager::start()
{
	cam_ = SceneManager::instance()->currentState()->getEntitiesWithComponent<Camera>()[0]->getComponent<Camera>();
	camTransform_ = cam_->getBrotherComponent<Transform>();
	matrix_ = SceneManager::instance()->currentState()->getEntitiesWithComponent<Camera>()[0]->getComponent<Matrix>();
	camTransform_->yaw(-45, REF_SYSTEM::GLOBAL);
}

bool CameraManager::handleEvent(unsigned int time)
{
	//Pillamos la info del ratón
	float mouseX = InputManager::getSingletonPtr()->getMouse()->getMouseState().X.abs;
	float mouseY = InputManager::getSingletonPtr()->getMouse()->getMouseState().Y.abs;
	Vector3 delta = { 0,0,0 };

	std::cout << "Mouse: {" << mouseX << "," << mouseY << "} \n";

	//AVANZAR/RETROCEDER
	if (mouseY < 2 * (float)OgreManager::instance()->getWindowSize(1) / 10)
		delta += (Vector3::UNIT_Y.crossProduct(camTransform_->right())) * 15;
	else if (mouseY > 8 * (float)OgreManager::instance()->getWindowSize(1) / 10)
		delta += (Vector3::UNIT_Y.crossProduct(camTransform_->right())) * -15;

	//IZQUIERDA/DERECHA
	if (mouseX < 2 * (float)OgreManager::instance()->getWindowSize(0) / 10)
		delta += camTransform_->right() * -15;
	else if (mouseX > 8 * (float)OgreManager::instance()->getWindowSize(0) / 10)
		delta += camTransform_->right() * 15;

	//ROTACIONES TODO:HACER QUE ORBITE ALREDEDOR DEL CENTRO
	if (InputManager::getSingletonPtr()->isKeyDown("RotaIzquierda") && !rotated_)
	{
		camTransform_->yaw(90, REF_SYSTEM::GLOBAL);
		rotated_ = true;
	}

	else if (InputManager::getSingletonPtr()->isKeyDown("RotaDerecha") && !rotated_)
	{
		camTransform_->yaw(-90, REF_SYSTEM::GLOBAL);
		rotated_ = true;
	}
	else
		rotated_ = false;

	//RAYCAST
	if (InputManager::getSingletonPtr()->isKeyDown("Ray")) 
		OgreManager::instance()->raycast();

	//Rueda del ratón para hacer zoom (no se como se pone esto en el archivo del input porque no son teclas como tales)
	//ZOOM IN/OUT
	if (InputManager::getSingletonPtr()->getMouse()->getMouseState().Z.rel > 0)
		delta += camTransform_->forward() * 50; //TODO: quitar el 50 y poner un parámetro de sensibilidad

	else if (InputManager::getSingletonPtr()->getMouse()->getMouseState().Z.rel < 0)
		delta += camTransform_->forward() * -50;

	//Move the camera
	moveCamera(delta);
	return false;
}

void CameraManager::moveCamera(Vector3 deltaPos)
{
	//TODO: HACER QUE EL CAMPO DE VISIÓN DÉ LA CÁMARA SEA UNA PIRÁMIDE INVERTIDA
	Vector3 newPos = camTransform_->getPosition() + deltaPos;
	//Up/down
	if (newPos.y < 50)
		newPos.y = 50;
	else if (newPos.y > 1000)
		newPos.y = 1000;

	//Left/right
	if (newPos.x < -500)
		newPos.x = -500;
	else if (newPos.x > 500)
		newPos.x = 500;

	//Forward/backwards
	if (newPos.z < -600)
		newPos.z = -600;
	else if (newPos.z > 1000)
		newPos.z = 1000;

	//Mueve la cámara
	camTransform_->setPosition(newPos);
}