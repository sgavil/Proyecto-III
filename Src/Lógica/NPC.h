#pragma once
#include <PARKEngine/Component.h>
#include "IndexPQ.h"
#include <stack>

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

	//Cola que indica los movimientos que seguirá el NPC
	std::stack<Node*> movements;

	//Velocidad
	float speed_;


	//Métodos auxiliares
	//Relaja el camino entre el primer nodo y el segundo
	void relax(int srcIndex, int destIndex);
	//Calcula el índice de una posición de la matriz (PONERLO EN MATRIX)
	int calculateIndex(int i, int j);
	//Dice si la adyacente es del formato correcto (no diagonal)
	bool adyacenteCorrecta(Vector2 src, Vector2 dst);
	//Indica si el NPC ya está en el nodo dado
	bool isInNode(Node* n);
	//Mueve al NPC al nodo indicado
	void moveToNode(Node* n, int deltaTime);
};

REGISTER_TYPE(NPC);