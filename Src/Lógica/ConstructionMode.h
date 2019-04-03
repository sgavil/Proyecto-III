#pragma once
#include "PARKEngine/Component.h"
#include <vector>
#include <algorithm>

using namespace std;

class Matrix;

class ConstructionMode : public Component
{
public:
	ConstructionMode();
	~ConstructionMode();

	virtual void load(json file);

	virtual void start();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(unsigned int time);
	virtual void receive(Message* msg) {};

private:
	Entity* matrixEntity_;
	Entity* nodeEntity_;
	Ogre::Vector3 nodePos_;
	vector<string> buildingTypes_;

	list<Entity*> getNodesToConstruct(Entity* node, Ogre::Vector3 mousePos, int tamX, int tamY);
	bool canConstruct(list<Entity*> nodes, int n);

	Ogre::Vector3 getPosToConstruct(list<Entity*> nodes, int tamX, int tamY);
	void setNodesType(string building, list<Entity*> nodes);
	void setBuilding(string building, list<Entity*> nodes, int tamX, int tamY);
};

REGISTER_TYPE(ConstructionMode)