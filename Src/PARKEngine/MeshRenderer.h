#pragma once
#include "Component.h"

class Transform;
class Ogre::SceneNode;
class Message;
class OgreManager;

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
	virtual bool handleEvent(unsigned int time) { return false; };
	virtual void receive(Message* msg);

	virtual void save(json& file) {};



	//Vuelve visible/invisible el renderer
	virtual void setVisible(bool b);

	//Sets the material of the mesh
	virtual void setMaterial(std::string materialName);
	//Returns the material of the mesh
	virtual std::string getMaterial();
	//Returns aabb of the mesh
	virtual void getAABB(Vector3& aabbMin, Vector3& aabbMax);

protected:
	friend class OgreManager;
	Transform * transform_ = nullptr;
	Ogre::SceneNode* node_;

	//Devuelve el nodo de Ogre
	virtual Ogre::SceneNode* getNode();

};

REGISTER_TYPE(MeshRenderer)