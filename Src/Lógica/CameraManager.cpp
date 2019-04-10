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
}

void CameraManager::setup(Matrix* matrix)
{
	//No se puede hacer en el start porque puede que la matriz no se haya creado toa
	cam_ = SceneManager::instance()->currentState()->getEntitiesWithComponent<Camera>()[0]->getComponent<Camera>();
	camTransform_ = cam_->getBrotherComponent<Transform>();

	Vector3 minNodePos = matrix->getEntityNode(0)->getComponent<Transform>()->getPosition();
	Vector3 maxNodePos = matrix->getEntityNode(matrix->getSize(0) * matrix->getSize(1) - 1)->getComponent<Transform>()->getPosition();
	minCorner = { minNodePos.x, minNodePos.z };
	maxCorner = { maxNodePos.x, maxNodePos.z };

	camTransform_->yaw(45, REF_SYSTEM::GLOBAL);
}

bool CameraManager::handleEvent(unsigned int time)
{
	//Pillamos la info del ratón
	float mouseX = InputManager::getSingletonPtr()->getMouse()->getMouseState().X.abs;
	float mouseY = InputManager::getSingletonPtr()->getMouse()->getMouseState().Y.abs;

	Vector3 delta = { 0,0,0 };

	//ADELANTE/ATRÁS
	if (mouseY < 2 * (float)OgreManager::instance()->getWindowSize(1) / 10)
		delta += (Vector3::UNIT_Y.crossProduct(camTransform_->right())) * 15;
	else if (mouseY > 8 * (float)OgreManager::instance()->getWindowSize(1) / 10)
		delta += (Vector3::UNIT_Y.crossProduct(camTransform_->right())) * -15;

	//IZQUIERDA/DERECHA
	if (mouseX < 2 * (float)OgreManager::instance()->getWindowSize(0) / 10)
		delta += camTransform_->right() * -15;
	else if (mouseX > 8 * (float)OgreManager::instance()->getWindowSize(0) / 10)
		delta += camTransform_->right() * 15;

	//Rueda del ratón para hacer zoom (no se como se pone esto en el archivo del input porque no son teclas como tales)
	//ZOOM IN/OUT
	if (InputManager::getSingletonPtr()->getMouse()->getMouseState().Z.rel > 0)
		delta += camTransform_->forward() * 50; //TODO: quitar el 50 y poner un parámetro de sensibilidad

	else if (InputManager::getSingletonPtr()->getMouse()->getMouseState().Z.rel < 0)
		delta += camTransform_->forward() * -50;

	//Move the camera
	if(delta.length() != 0)
		moveCamera(delta);

	//ROTACIONES TODO:HACER QUE ORBITE ALREDEDOR DEL CENTRO
	if (InputManager::getSingletonPtr()->isKeyDown("RotaIzquierda") && !rotated_)
	{
		//Vector3 focus = OgreManager::instance()->raycast().second;
		//rotateAround(Vector3(focus.x, camTransform_->getPosition().y, focus.z), -90);
		camTransform_->yaw(-90, REF_SYSTEM::GLOBAL);
		rotated_ = true;
	}

	else if (InputManager::getSingletonPtr()->isKeyDown("RotaDerecha") && !rotated_)
	{
		camTransform_->yaw(90, REF_SYSTEM::GLOBAL);
		rotated_ = true;
	}
	else
		rotated_ = false;
	return false;
}
void CameraManager::rotateAround(Vector3 center, float degrees)
{
	//Posición de la cámara
	Vector3 camPos = camTransform_->getPosition();

	//Hallamos el radio de la órbita
	float radius = center.distance(camPos);

	//Pasamos el ángulo a radianes
	float angle = Radian(Degree(degrees)).valueRadians();

	//Hallamos la nueva posición
	float newX = sin(angle)*radius + camPos.x;
	float newZ = cos(angle)*radius + camPos.z;

	//Move the camera
	Vector3 newPos = Vector3(newX, camPos.y, newZ);
	Vector3 delta = newPos - camPos;
	moveCamera(delta);

	//Rotate the camera
	camTransform_->yaw(degrees, REF_SYSTEM::GLOBAL);
}


void CameraManager::moveCamera(Vector3 deltaPos)
{
	//Note that what we want to be inside the map isn't the camera itself, but the point 
	//which it is heading (the "focus"). Therefore, we make the calculus with this focus in mind
	//(except for the Y coordinate)

	//Move the camera towards the desired place and throw another ray
	camTransform_->translate(deltaPos);

	//If the second ray is out of the matrix (get back to where you once belonged)
	if (OgreManager::instance()->raycast(0.5, 0.5).first == nullptr)
		camTransform_->translate(-deltaPos);
}