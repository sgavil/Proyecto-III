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
	virtual bool handleEvent(unsigned int time);
	virtual void receive(Message* msg) {};

	//Devuelve el nodo de Ogre
	virtual Ogre::SceneNode* getNode() { return node_; };

protected:
	Transform * transform_ = nullptr;
	Ogre::SceneNode* node_;

};

REGISTER_TYPE(MeshRenderer)