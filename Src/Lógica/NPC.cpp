#include "NPC.h"
#include <iostream>
#include  <PARKEngine/Entity.h>
#include <PARKEngine/PARKComponents.h>
#include <PARKEngine/OgreIncludes.h>
#include <PARKEngine/PARKManagers.h>
#include "Matrix/Node.h"
#include "Matrix/Matrix.h"
#include <limits>

NPC::NPC():pq(0), hasPath(false)
{
}

NPC::~NPC()
{
}
void NPC::start()
{
	matrix_ = SceneManager::instance()->currentState()->getEntitiesWithComponent<Matrix>()[0]->getComponent<Matrix>();
	//entity_->getComponent<Rigidbody>()->setPosition(entity_->getComponent<Rigidbody>()->getPosition() + Vector3(-500, 0, 0));
	//entity_->getComponent<MeshRenderer>()->setMaterial("Ogre.material");
	
}

void NPC::update(unsigned int time)
{
	if(hasPath)
	{
		std::cout << getEntity()->getName() << " MOVING" << std::endl;
	}
	//std::cout << entity_->getComponent<MeshRenderer>()->getMaterial() << std::endl;
	//entity_->getComponent<Transform>()->rotate(Vector3::UNIT_Y, 2);
	//entity_->getComponent<Transform>()->translate(Vector3(1, 0, 0));
	//entity_->getComponent<Rigidbody>()->setPosition(entity_->getComponent<Rigidbody>()->getPosition() + Vector3(-500, 0, 0));
	//std::cout << entity_->getComponent<Rigidbody>()->getInfo();
	//entity_->getComponent<Transform>()->scale(Vector3(0.9, 0.9, 0.9));
	//std::cout << "Hola, soy " << entity_->getName() << " y tengo \n Hambre: " << hunger_ << "\n Pipí: " << peepee_ << "\n Diversión: " << fun_ << std::endl;
}

void NPC::setNode(Node * node)
{
	node_ = node;
}

Node * NPC::getNode()
{
	return node_;
}

void NPC::load(json file)
{
	hunger_ = file["hunger"];
	peepee_ = file["peepee"];
	fun_ = file["fun"];
}

void NPC::lookForPaths()
{
	int N = matrix_->getSize(0) * matrix_->getSize(1);
	std::cout << N << endl;
	distTo = std::vector<int>(N);
	nodeTo = std::vector<int>(N);

	//Inicializamos las distancias a infinito
	for (int v = 0; v < N; v++)
		distTo[v] = numeric_limits<int>::max();
	
	//Metemos el nodo actual con prioridad 0
	Vector2 nodePos = node_->getMatrixPos();
	int nodeIndex = calculateIndex(nodePos.y, nodePos.x); //TODO: PONER NUMERO DE COLUMNAS
	pq.push(nodeIndex, 0);
	distTo[0] = 0; //Distancia 0

	bool atraccion = false;
	//Vamos metiendo y sacando elementos de la cola de prioridades variables
	while (!pq.empty() && !atraccion)
	{
		IndexPQ<int>::Par n = pq.top();
		pq.pop();
		list<Node*> ady = matrix_->getAdj(n.elem);
		for (Node* n : ady)
		{
			Vector2 adyPos = n->getMatrixPos();
			relax(nodeIndex, calculateIndex(adyPos.y, adyPos.x));
		}
	}
	hasPath = true;
}

void NPC::relax(int srcIndex, int destIndex)
{
	if (distTo[destIndex] > distTo[srcIndex] + 1) 
	{
		//Añadimos el tiempo de espera de la página en si
		distTo[destIndex] = distTo[srcIndex] + 1;
		nodeTo[destIndex] = srcIndex;
		//En la función update se contempla que la clave no estuviera ya
		pq.update(destIndex, distTo[destIndex]);
	}
}

int NPC::calculateIndex(int i, int j)
{
	return i * matrix_->getSize(1) + j;
}

bool NPC::handleEvent(unsigned int time)
{
	if (InputManager::getSingletonPtr()->isKeyDown("NPC"))
		lookForPaths();
	return false;
}