#include "CameraManager.h"
#include "PARKEngine/PARKEngine.h"
#include "Matrix/Matrix.h"


CameraManager::CameraManager()
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
	camTransform_->yaw(45, REF_SYSTEM::GLOBAL);
}

void CameraManager::load(json file)
{
	addParameter(MAX_HEIGTH, file["maxHeigth"]);
	addParameter(MIN_HEIGTH, file["minHeigth"]);
}


bool CameraManager::handleEvent(unsigned int time)
{
	//Standard increment (for camera transfomations)
	float stdIncr = ((float)time / 2);

	//Pillamos la info del ratón
	float mouseX = InputManager::getSingletonPtr()->getMouse()->getMouseState().X.abs;
	float mouseY = InputManager::getSingletonPtr()->getMouse()->getMouseState().Y.abs;

	Vector3 delta = { 0,0,0 };

	//ADELANTE/ATRÁS
	if (mouseY < 2 * (float)OgreManager::instance()->getWindowSize(1) / 10)
		delta += Vector3::UNIT_Y.crossProduct(camTransform_->right()) * stdIncr;
	else if (mouseY > 8 * (float)OgreManager::instance()->getWindowSize(1) / 10)
		delta += Vector3::UNIT_Y.crossProduct(camTransform_->right()) * -stdIncr;

	//IZQUIERDA/DERECHA
	if (mouseX < 2 * (float)OgreManager::instance()->getWindowSize(0) / 10)
		delta += camTransform_->right() * -stdIncr;
	else if (mouseX > 8 * (float)OgreManager::instance()->getWindowSize(0) / 10)
		delta += camTransform_->right() * stdIncr;

	//Rueda del ratón para hacer zoom (no se como se pone esto en el archivo del input porque no son teclas como tales)
	//ZOOM IN/OUT
	if (InputManager::getSingletonPtr()->getMouse()->getMouseState().Z.rel > 0)
		delta += camTransform_->forward() * stdIncr * 1.5; //TODO: poner un parámetro de sensibilidad

	else if (InputManager::getSingletonPtr()->getMouse()->getMouseState().Z.rel < 0)
		delta += camTransform_->forward() * stdIncr * -1.5;

	//Move the camera
	if(delta.length() != 0)
		moveCamera(delta);

	//ROTACIONES
	if (InputManager::getSingletonPtr()->isKeyDown("RotaIzquierda"))
		orbit(-90);
	else if (InputManager::getSingletonPtr()->isKeyDown("RotaDerecha"))
		orbit(90);

	return false;
}


void CameraManager::orbit(float degrees)
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
}
void CameraManager::moveCamera(Vector3 deltaPos)
{
	//Note that what we want to be inside the map isn't the camera itself, but the point 
	//which it is heading (the "focus"). Therefore, we make the calculus with this focus in mind
	//(except for the Y coordinate)

	//Move the camera towards the desired place and throw another ray
	camTransform_->translate(deltaPos);

	//If the second ray is out of the matrix or we want to go too up/down
	float y = camTransform_->getPosition().y;
	if (OgreManager::instance()->raycast().first == nullptr || y > MAX_HEIGTH || y < MIN_HEIGTH)
		camTransform_->translate(-deltaPos);
}