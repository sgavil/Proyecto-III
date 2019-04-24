#pragma once
#include "PARKEngine/Component.h"
#include <vector>
#include <algorithm>

using namespace std;

class Matrix;
class Edificio;

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

	virtual void buildInMatrix(int i, int j, std::string name);

private:
	bool constructActive_;
	bool canConst_;
	Entity* matrixEntity_;
	Entity* nodeEntity_;
	Edificio* build_;
	Entity* buildingEntity_;
	list<Entity*> nodes_;
	vector<string> buildingTypes_;

	void construct(string bName, unsigned int time);
	list<Entity*> getNodesToConstruct(Entity* node, Ogre::Vector3 mousePos);
	bool canConstruct(int n);

	Ogre::Vector3 getPosToConstruct();
	void setNodesType();
	void setBuilding();
	void createEntryExitRoad(string roadName);
	void setEntryExit();
	void setNodeMaterial(bool enable, bool can);
};

REGISTER_TYPE(ConstructionMode)