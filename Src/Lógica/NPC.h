#pragma once
#include <PARKEngine/Component.h>

class Node;

class NPC : public Component
{
public:
	NPC();
	~NPC();

	//Load and start methods
	void load(json file);
	void start();
	
	//Generic methods
	virtual void update(unsigned int time);

	//Set current node
	void setNode(Node* node);
	//Gets current node
	Node* getNode();

private:
	//Necesidades
	int hunger_;
	int peepee_;
	int fun_;

	//Puntero al nodo de la matriz en que se encuentra
	Node* node_;
};

REGISTER_TYPE(NPC);