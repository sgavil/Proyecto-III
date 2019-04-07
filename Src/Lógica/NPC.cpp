#include "NPC.h"
#include <iostream>
#include  <PARKEngine/Entity.h>
#include <PARKEngine/PARKComponents.h>
#include <PARKEngine/OgreIncludes.h>
#include <PARKEngine/PARKManagers.h>
#include "Matrix/Node.h"
#include "Matrix/Matrix.h"
#include <limits>

NPC::NPC():pq(0), hasPath(false), totalTime_(0)
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
		Node* n = movements.top();
		//Not in that node yet
		if(node_ != n)
		{
			//Move towards next node
			Transform* trans = getEntity()->getComponent<Transform>();
			Transform* nextTrans = n->getEntity()->getComponent<Transform>();
			//Vector unitario
			Vector3 delta = (nextTrans->getPosition() - trans->getPosition());
			delta.normalise();
			//Lo multiplicamos por el deltaTime y la velocidad del NPC
			delta = delta * speed_ * (time/10);
			delta.y = 0;//We dont want to move in that axis
			std::cout << "Delta: [" << delta.x << ", " << delta.y << ", " << delta.z << "]" << std::endl;
			trans->translate(delta);
			if (isInNode(n))
				node_ = n;
			//std::cout << getEntity()->getName() << " MOVING TO {" << n->getMatrixPos().x << ", " << n->getMatrixPos().y << "}" << std::endl;
		}
		else
		{
			//Change node material for debugging
			n->getEntity()->getComponent<MeshRenderer>()->setVisible(true);
			n->getEntity()->getComponent<MeshRenderer>()->setMaterial("Road");
			//Pop movement
			movements.pop();

			//If path ended
			if (movements.empty())
				hasPath = false;
		}
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
	speed_ = file["speed"];
}

void NPC::lookForPaths()
{
	//PRUEBA
	matrix_->getEntityNode(21, 20)->getComponent<Node>()->setType("Amusement");

	//Pillamos variables
	int N = matrix_->getSize(0) * matrix_->getSize(1);
	pq = IndexPQ<int>(N);
	distTo = std::vector<int>(N);
	nodeTo = std::vector<int>(N);

	//Inicializamos las distancias a infinito
	for (int v = 0; v < N; v++)
		distTo[v] = numeric_limits<int>::max();

	
	//Metemos el nodo actual con prioridad 0
	Vector2 nodePos = node_->getMatrixPos(); //ESTO TAMBIÉN ESTÁ AL REVÉS
	int nodeIndex = calculateIndex(nodePos.y, nodePos.x);
	pq.push(nodeIndex, 0);
	distTo[0] = 0; //Distancia 0
	nodeTo[0] = 0;

	bool atraccion = false;
	Node* nodoActual = nullptr;
	//Vamos metiendo y sacando elementos de la cola de prioridades variables
	while (!pq.empty() && !atraccion)
	{
		IndexPQ<int>::Par n = pq.top();
		nodoActual = matrix_->getEntityNode(n.elem)->getComponent<Node>();
		if (nodoActual->getType() == "Amusement")
		{
			atraccion = true;
			break;
		}
		
		pq.pop();
		list<Entity*> ady = matrix_->getAdj(nodoActual->getEntity(), 1, 1); //radio de 1
		//Adyacentes al nodo actual

		for (Entity* e : ady)
		{
			Vector2 srcPos = nodoActual->getMatrixPos();
			Vector2 adyPos = e->getComponent<Node>()->getMatrixPos();
			//Quitamos diagonales y la propia casilla
			if(adyacenteCorrecta(srcPos, adyPos)) // && e->getComponent<Node>()->getType() == "Empty"
				relax(n.elem, calculateIndex(adyPos.y, adyPos.x));
		}
	}

	//Rellenamos la cola de movimientos
	if (atraccion)
	{
		int index = calculateIndex(nodoActual->getMatrixPos().y, nodoActual->getMatrixPos().x); //ESTO TAMBIÉN ESTÁ AL REVÉS
		while (nodeTo[index] != index)
		{
			//Get node 
			Node* n = matrix_->getEntityNode(index)->getComponent<Node>();
			//Put it in the element list
			movements.push(n);
			//Previous index
			index = nodeTo[index];
		}
		std::cout << "YENDO A LA ATRACCIÓN" << std::endl;
		hasPath = true;
	}
	else
		std::cout << "NO HAY ATRACCIONES DISPONIBLES" << std::endl;
}

void NPC::relax(int srcIndex, int destIndex)
{
	//std::cout << "Relaxing from " << srcIndex << " to" << destIndex << std::endl;
	if (distTo[destIndex] > distTo[srcIndex] + 1)
	{
		//Añadimos el tiempo de espera de la página en si
		distTo[destIndex] = distTo[srcIndex] + 1;
		nodeTo[destIndex] = srcIndex;
		//En la función update se contempla que la clave no estuviera ya
		pq.update(destIndex, distTo[destIndex]);
		//std::cout << "METIDO EN LA COLA EL " << destIndex << std::endl;
	}
}

int NPC::calculateIndex(int i, int j)
{
	return i * matrix_->getSize(1) + j;
}

bool NPC::handleEvent(unsigned int time)
{
	if (InputManager::getSingletonPtr()->isKeyDown("NPC"))
	{
		//Get initial node
		Entity* initialNode = matrix_->getEntityNode(0, 0); //ESTÁN AL REVÉS FILAS Y COLUMNAS
		node_ = initialNode->getComponent<Node>();
		//Set position to it
		Vector3 pos = initialNode->getComponent<Transform>()->getPosition();
		getEntity()->getComponent<Transform>()->setPosition(pos + Vector3(0,10,0));
		//Look for paths
		lookForPaths();
	}
	
	return false;
}


bool NPC::adyacenteCorrecta(Vector2 src, Vector2 dst)
{
	//Es una goddamn puerta XOR
	return ((src.x == dst.x || src.y == dst.y) && (src.x != dst.x || src.y != dst.y));
}

bool NPC::isInNode(Node* n)
{
	Vector3 nodeSize = matrix_->getNodeSize();
	Vector3 newNodeMin = n->getEntity()->getComponent<Transform>()->getPosition() - nodeSize / 4;
	Vector3 newNodeMax = n->getEntity()->getComponent<Transform>()->getPosition() + nodeSize / 4;

	//Check AABB
	Vector3 actualPos = getEntity()->getComponent<Transform>()->getPosition();
	if (actualPos.x > newNodeMin.x && actualPos.x < newNodeMax.x && actualPos.z > newNodeMin.z && actualPos.z < newNodeMax.z)
		return true;
	return false;
}