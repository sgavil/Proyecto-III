#include "Camera.h"

#include "Entity.h"
#include "Transform.h"

#include "OgreManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "OgreIncludes.h"


#include <CEGUI/CEGUI.h>
#include <SDL_video.h>


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::start()
{
	//Camera already created
	if (OgreManager::instance()->getCamera() != nullptr)
		camera_ = OgreManager::instance()->getCamera();
	//Create a new one
	else
		camera_ = OgreManager::instance()->createCamera("Camera", 5, 50000, true);

	camNode_ = (Ogre::SceneNode*)camera_->getParentNode();
	camera_->getViewport()->setClearEveryFrame(true);
	//Initialises it 
	transform_ = entity_->getComponent<Transform>();
	if (transform_ == nullptr)
		std::cout << "ERROR: ENTITY " + entity_->getName() + " IS LACKING TRANSFORM COMPONENT" << std::endl;
	//Initialise camNode
	else
	{
		Vector3 pos = transform_->getPosition();
		camNode_->setPosition(pos);
		camNode_->lookAt(Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
		transform_->setRotation(camNode_->getOrientation());
	}
}

void Camera::update(unsigned int time)
{
}

void Camera::receive(Message* msg)
{
	if(msg->mType_ == MessageId::TRANSFORM_CHANGED)
	{
		camNode_->setPosition(transform_->getPosition());
		camNode_->setOrientation(transform_->getRotation());
	}
}

void Camera::save(json& file)
{
	//Comprobamos si existe o no el nombre y si no es así , lo creamos
	
	auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");
	file["Entities"][0] = json::parse("\"name\": Camera");
	//Guardamos el componente y si no existe el array de componentes, lo creamos

	////guardar el nombre de la entidad en caso de que no exista
	//bool found = false;
	//json entidad;
	//for (const auto& obj : file["Entities"]) {
	//	if(obj["name"]==entity_->getName()){
	//		found = !found;	
	//		entidad = obj;
	//		break;
	//	}
	//}
	//if(!found)
	//file.push_back(json::object_t::value_type("name", entity_->getName()));

	////Inserte componente en la entidad, y si aún no hay ninguno, crear el array de componentes
	//else{	

	//	auto it = entidad.find("Components");
	//	if (it == entidad.end()) {
	//		//Creamos el array componentes
	//		entidad.push_back("Components");
	//		json componentes = json::array();
	//		componentes.push_back(json::object_t::value_type("name", entity_->getName()));
	//		entidad["Components"].push_back(componentes);
	//	}
	//	else {
	//		entidad["Components"].push_back(json::object_t::value_type("name", entity_->getName()));
	//	}
	//}
}
