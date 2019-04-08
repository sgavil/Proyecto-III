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
	virtual void update(unsigned int time);
	virtual bool handleEvent(unsigned int time);
	virtual void receive(Message* msg) {};

private:
	bool constructActive_;
	bool canConst_;
	Entity* matrixEntity_;
	Entity* nodeEntity_;
	list<Entity*> nodes_;
	vector<string> buildingTypes_;

	list<Entity*> getNodesToConstruct(Entity* node, Ogre::Vector3 mousePos, int tamX, int tamY);
	bool canConstruct(int n);

	Ogre::Vector3 getPosToConstruct(int tamX, int tamY);
	void setNodesType(string building);
	void setBuilding(string building, int tamX, int tamY);
	void setNodeMaterial(bool enable, bool can);
};

REGISTER_TYPE(ConstructionMode)