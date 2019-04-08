#pragma once
#include "PARKEngine/Entity.h"
#include "PARKEngine/Transform.h"
#include "PARKEngine/MeshRenderer.h"
#include "PARKEngine/SceneManager.h"
#include "Node.h"

#include <vector>

using namespace std;
class Matrix : public Component
{
public:
	Matrix();
	~Matrix();

	virtual void start();

	virtual void load(json file);

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(unsigned int time) { return false; };
	virtual void receive(Message* msg) {};

	vector<vector<Entity*>> getMatrix();
	Entity* getEntityNode(int i, int j);
	list<Entity*> getAdj(Entity* e, int x, int y);

	//Devuelve adyacentes especificando indice
	Entity* getEntityNode(int index);
	//Pa pillar el tamaño
	int getSize(int i) { if (i == 1) return matrix_.size(); else return matrix_.at(0).size(); };

	Ogre::Vector3 getNodeSize();
	bool limits(int i, int j);

private:
	Ogre::Vector2 mSize_;
	Ogre::Vector3 nSize_;
	vector<vector<Entity*>> matrix_;
	std::list<Component*> comps;
	
	void createMatrix();
	Vector3 getPosIni();
};

REGISTER_TYPE(Matrix)