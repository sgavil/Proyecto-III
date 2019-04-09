#pragma once
#include <PARKEngine/Component.h>
#include "IndexPQ.h"
#include <stack>
#include <string>

class Node;
class Matrix;

//Estadística del NPC. Indica el nombre del stat, sus valores actual y máximo, y si aumenta/disminuye con el tiempo
struct Stat
{
	Stat(std::string name, float value, float maxVal, bool decreases)
	{
		name_ = name;
		value_ = value;
		MAX_VALUE = maxVal;
		decreases_ = decreases;
	}
	Stat(){}
	std::string name_;
	float value_;
	float MAX_VALUE;
	bool decreases_;
};

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

	//Looks for a certain bulding 
	void lookForBuildings();
	//Walks by without a destiny
	void deambulate();

	//GETTERS
	float getFun() { return fun_.value_; };
	float getHunger() { return hunger_.value_; };
	float getPeepee() { return peepee_.value_; };


private:
	//ATRIBUTOS DE JSON
	//Necesidades
	Stat fun_;
	Stat hunger_;
	Stat peepee_;


	//Velocidad
	float speed_;
	//Velocidad a la que bajan las necesidades
	float exigency_;

	//Camino
	bool hasPath;
	//Está en una atracción
	bool isInBuilding_;



	//Puntero a la matriz
	Matrix* matrix_;
	//Puntero al nodo de la matriz en que se encuentra
	Node* node_;

	//PARA EL ALGORITMO
	//Para hacer el algoritmo de Dijkstra
	IndexPQ<int> pq; //Cola de prioridad 
	std::vector<int > distTo; //Distancia entre el nodo inicial y los demás
	std::vector<int > nodeTo; //Indicador del camino que hacemos
	//Cola que indica los movimientos que seguirá el NPC
	std::stack<Node*> movements;


	//MÉTODOS AUXILIARES
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
	//Cambia una stat del NPC una cierta cantidad
	void changeStat(Stat& stat, float incr);
};

REGISTER_TYPE(NPC);