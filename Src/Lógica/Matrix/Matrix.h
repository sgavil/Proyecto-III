#pragma once
#include "Arquitectura/Entity.h"
#include "Arquitectura/Transform.h"
#include "Arquitectura/MeshRenderer.h"
#include "Scenes/SceneManager.h"
#include "Node.h"

using namespace std;
using M = vector<vector<Entity*>>;
using dirs = vector<pair<int, int>>;

class Matrix : public Component
{
public:
	Matrix();
	~Matrix();

	virtual void start();

	virtual void load(json file);

	virtual void render(unsigned int time);
	virtual void update(unsigned int time);
	virtual bool handleEvent(unsigned int time) { return false; };
	virtual void receive(Message* msg) {};

	M getMatrix();
	Entity* getEntityNode(int i, int j);
	list<Entity*> getAdj(Entity* e);
	list<Entity*> getAdj(int i, int j);

private:
	dirs dirs_;
	Vector2 mSize_;
	Vector3 nSize_;
	M matrix_;
	std::list<Component*> comps;
	
	void createMatrix();
	Vector3 getPosIni();
	bool limits(int i, int j);
};

REGISTER_TYPE(Matrix)