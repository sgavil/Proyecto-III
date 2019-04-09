#pragma once
#include "PARKEngine/Component.h"

using namespace std;

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

	void setMatrixPos(int i, int j);
	//Devuelve la posición en la matriz (fila, columna)
	Vector2 getMatrixPos();

	string getType();
	void setType(string t);

private:
	Ogre::Vector2 posMatrix_;
	string nodeType_;

	//Componente asociado al edificio

};

REGISTER_TYPE(Node)