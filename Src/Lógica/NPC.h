#pragma once
#include <PARKEngine/Component.h>
#include "IndexPQ.h"

class Node;
class Matrix;

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
	virtual bool handleEvent(unsigned int time);

	//Set current node
	void setNode(Node* node);
	//Gets current node
	Node* getNode();

	//Applies dijkstra algorithm
	void lookForPaths();

private:
	//Necesidades
	int hunger_;
	int peepee_;
	int fun_;

	//Camino
	bool hasPath;

	//Puntero a la matriz
	Matrix* matrix_;
	//Puntero al nodo de la matriz en que se encuentra
	Node* node_;

	//Para hacer el algoritmo de Dijkstra
	IndexPQ<int> pq; //Cola de prioridad
	std::vector<int > distTo; //Distancia entre el nodo inicial y los demás
	std::vector<int > nodeTo; //Indicador del camino que hacemos

	//Métodos privados
	//Relaja la arista actual
	void relax(int srcIndex, int destIndex);
	//Calcula el índice de una posición de la matriz (PONERLO EN MATRIX)
	int calculateIndex(int i, int j);


};

REGISTER_TYPE(NPC);