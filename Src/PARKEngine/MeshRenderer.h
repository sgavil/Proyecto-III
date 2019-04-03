#pragma once
#include "Component.h"

class Transform;
class Ogre::SceneNode;
class Message;

class MeshRenderer : public Component
{
public:
	MeshRenderer();

	//Crea una entidad renderizable a partir del nombre de su malla y una posición inicial
	MeshRenderer(std::string meshName, bool visible = true);

	~MeshRenderer();

	virtual void start();

	virtual void load(json file);

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(unsigned int time) { return false; };
	virtual void receive(Message* msg) {};

	//Devuelve el nodo de Ogre
	virtual Ogre::SceneNode* getNode(); //ESTO HAY QUE QUITARLO

	//Vuelve visible/invisible el renderer
	virtual void setVisible(bool b);

	//Sets the material of the mesh
	virtual void setMaterial(std::string materialName);
	//Returns the material of the mesh
	virtual std::string getMaterial();

protected:
	Transform * transform_ = nullptr;
	Ogre::SceneNode* node_;

};

REGISTER_TYPE(MeshRenderer)