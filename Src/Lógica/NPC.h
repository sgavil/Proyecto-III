#pragma once
#include <PARKEngine/Component.h>
#include "IndexPQ.h"
#include <stack>
#include <string>

class Node;
class Matrix;
class Edificio;

//Estadística del NPC. Indica el nombre del stat, sus valores actual y máximo, la exigencia(velocidad a la que cambia y cuánto recupera)
//, y si aumenta/disminuye con el tiempo
class Stat
{
public:
	Stat(std::string name, float value, float maxVal, float exigency, bool decreases)
	{
		name_ = name;
		value_ = value;
		MAX_VALUE = maxVal;
		exigency_ = exigency;
		decreases_ = decreases;
	}
	
	//Restaura una cierta cantidad del stat
	void restore(float amount)
	{
		amount /= exigency_;

		if (!decreases_)
			amount *= -1;
		value_ += amount;

		checkValue();
	}

	//Recupera una cierta cantidad del stat
	void consume(float amount, bool relative = false)
	{
		amount *= exigency_;

		//Para ajustarlo a la stat en cuestión
		if (relative)
			amount /= MAX_VALUE;

		//Le quitamos el icremento y comprobamos límites
		if (decreases_)
			amount *= -1;
		value_ += amount;

		checkValue();
	}


	Stat(){}

	std::string name_;
	float value_;
	float MAX_VALUE;
	float exigency_;
	bool decreases_;

private:
	//Comprueba que no nos pasamos de los límites
	void checkValue()
	{
		if (value_ < 0)
			value_ = 0;
		else if (value_ > MAX_VALUE)
			value_ = MAX_VALUE;
	}
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

	//Returns a string with indented information of the NPC
	virtual std::string getInfo();

	//Set current node
	void setNode(Node* node);
	//Gets current node
	Node* getNode();

	//Looks for a certain bulding 
	void lookForBuildings();
	//Walks by without a destiny
	void deambulate(unsigned int time);
	//Saca al NPC de la atracción
	void getOutofAttraction();

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

	//Para el modo deambular
	//Puntero al nodo anterior y siguiente
	Node* prevNode_;
	Node* nextNode_;

	//Edificio actual
	Edificio* actualBuilding_;


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
	//Follows current path
	void followPath(unsigned int time);
	//Encuentra el edificio a partir de su nodo de entrada
	Edificio* NPC::getBuilding(Node* eNode);
	//Indica si necesitamos algo
	bool lowStats();
	//Indica la stat más baja
	const Stat& lowerStat();
	//Entra en la atracción
	void enterAttraction();
};

REGISTER_TYPE(NPC);