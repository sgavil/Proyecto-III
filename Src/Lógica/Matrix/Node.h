#pragma once
#include "Arquitectura/Component.h"

using namespace std;

enum NodeType{EMPTY, ROAD, BUILDING_ENTRY, BUILDING_EXIT};

class Node : public Component
{
public:
	Node();
	~Node();

	virtual void load(json file);

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(unsigned int time) { return false; };
	virtual void receive(Message* msg) {};


	Vector2 getMatrixPos();
	Vector3 getNodeSize();

	NodeType getType();
	void setType(NodeType t);

private:
	Vector3 size_;
	Vector2 posMatrix_;
	NodeType nodeType_;

	//Componente asociado al edificio

};

REGISTER_TYPE(Node)