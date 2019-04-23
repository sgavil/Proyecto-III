#include "NPC.h"
#include <iostream>
#include <PARKEngine/PARKEngine.h>
#include "Matrix/Node.h"
#include "Matrix/Matrix.h"
#include <limits>
#include <cmath>

NPC::NPC():pq(0), hasPath(false), isInBuilding_(false), node_(nullptr), prevNode_(nullptr), nextNode_(nullptr)
{
}

NPC::~NPC()
{
}
void NPC::start()
{
	//Gets matrix
	matrix_ = SceneManager::instance()->currentState()->getEntitiesWithComponent<Matrix>()[0]->getComponent<Matrix>();

	//PRUEBA
	matrix_->getEntityNode(0)->getComponent<Node>()->setType("Road");
	matrix_->getEntityNode(0, 2)->getComponent<MeshRenderer>()->setMaterial("Road");


	//Get initial node
	Entity* initialNode = matrix_->getEntityNode(0, 0); //ESTÁN AL REVÉS FILAS Y COLUMNAS
	node_ = prevNode_ = initialNode->getComponent<Node>();
	//Set position to it
	Vector3 pos = initialNode->getComponent<Transform>()->getPosition();
	getBrotherComponent<Transform>()->setPosition(pos + Vector3(0, 10, 0));
}

void NPC::update(unsigned int time)
{
	//Bajar las necesidades (solo si no está en una atracción)
	if(!isInBuilding_)
	{
		float delta = ((float)time / 1000) * exigency_;
		changeStat(fun_, -delta);
		changeStat(hunger_, delta);
		changeStat(peepee_, delta);
	}
	//std::cout << entity_->getName() << "\n" << fun_.name_ << ": " << getFun() << "\n " << 
		//hunger_.name_ << ": " << getHunger() << "\n " << peepee_.name_ << ": " << getPeepee() << std::endl;

	//1. NPC has an avaiable path
	if (hasPath)
		followPath(time);
	//2. NPC is deambulating
	else
		deambulate(time);
}

void NPC::followPath(unsigned int time)
{
	Node* n = movements.top();
	//Not in that node yet (move towards it)
	if (node_ != n)
		moveToNode(n, time);
	//Arrived to the node
	else
	{
		//Pop movement
		movements.pop();
		//If path ended
		if (movements.empty())
			hasPath = false;
	}
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
	speed_ = file["speed"];
	exigency_ = file["exigency"];

	json stat = file["stats"];
	fun_ = Stat(stat[0]["name"], stat[0]["value"], stat[0]["maxValue"], stat[0]["decreases"]);
	hunger_ = Stat(stat[1]["name"], stat[1]["value"], stat[1]["maxValue"], stat[1]["decreases"]);
	peepee_ = Stat(stat[2]["name"], stat[2]["value"], stat[2]["maxValue"], stat[2]["decreases"]);
}

void NPC::lookForBuildings()
{
	//Pillamos variables
	int N = matrix_->getSize(0) * matrix_->getSize(1);
	pq = IndexPQ<int>(N);
	distTo = std::vector<int>(N);
	nodeTo = std::vector<int>(N);

	//Inicializamos las distancias a infinito
	for (int v = 0; v < N; v++)
		distTo[v] = numeric_limits<int>::max();

	
	//Metemos el nodo actual con prioridad 0
	Vector2 nodePos = node_->getMatrixPos();
	int nodeIndex = calculateIndex(nodePos.x, nodePos.y);
	pq.push(nodeIndex, 0);
	distTo[nodeIndex] = 0; //Distancia 0
	nodeTo[nodeIndex] = nodeIndex;

	bool atraccion = false;
	Node* nodoActual = nullptr;
	//Vamos metiendo y sacando elementos de la cola de prioridades variables
	while (!pq.empty() && !atraccion)
	{
		IndexPQ<int>::Par n = pq.top();
		nodoActual = matrix_->getEntityNode(n.elem)->getComponent<Node>();
		pq.pop();
		std::list<Entity*> ady = matrix_->getAdj(nodoActual->getEntity(), 1, 1); //radio de 1
		//Adyacentes al nodo actual
		for (Entity* e : ady)
		{
			Vector2 srcPos = nodoActual->getMatrixPos();
			Vector2 adyPos = e->getComponent<Node>()->getMatrixPos();
			//Quitamos diagonales y la propia casilla
			if (adyacenteCorrecta(srcPos, adyPos))
			{
				//Amusement found
				if (e->getComponent<Node>()->getType() == "Patitos" || e->getComponent<Node>()->getType() == "Burguer")
				{
					nodoActual = e->getComponent <Node>();
					relax(n.elem, calculateIndex(adyPos.x, adyPos.y));
					atraccion = true;
					break;
				}
				//Explore other nodes
				else if(e->getComponent<Node>()->getType() == "Road")
					relax(n.elem, calculateIndex(adyPos.x, adyPos.y));
			}
		}
	}

	//Rellenamos la cola de movimientos
	if (atraccion)
	{
		int index = calculateIndex(nodoActual->getMatrixPos().x, nodoActual->getMatrixPos().y); 
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

void NPC::deambulate(unsigned int time)
{
	//Where to go?
	if (nextNode_ == nullptr)
	{
		//1. FILTRAMOS LAS CASILLAS ADYACENTES
		std::list<Entity*> ady = matrix_->getAdj(node_->getEntity(), 1, 1); //radio de 1
		std::list<Entity*>::iterator it = ady.begin();
		std::vector<Node*> candidates;
		while (it != ady.end())
		{
			Node* adyNode = (*it)->getComponent<Node>();
			Vector2 srcPos = node_->getMatrixPos();
			Vector2 adyPos = adyNode->getMatrixPos();
			//1. Adyacente correcta   2. Es un camino  3. No venimos de ahí
			if (adyacenteCorrecta(srcPos, adyPos) && adyNode->getType() == "Road" && adyNode != prevNode_)
				candidates.push_back(adyNode);
			it++;
		}


		//2. ELEGIR UN NODO
		//Solo hay una dirección (volvemos)
		if (candidates.size() == 0)
		{
			if (prevNode_ != node_)
				nextNode_ = prevNode_;
		}
		else
		{
			int index = std::rand() % candidates.size();
			nextNode_ = candidates.at(index);
		}
	}
	else
		moveToNode(nextNode_, time);
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
	}
}

int NPC::calculateIndex(int i, int j)
{
	return i * matrix_->getSize(1) + j;
}

bool NPC::handleEvent(unsigned int time)
{
	if (InputManager::getSingletonPtr()->isKeyDown("NPC") && !hasPath)
	{
		//Looks for buildings
		lookForBuildings();
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
	Vector3 newNodeMin = n->getBrotherComponent<Transform>()->getPosition() - nodeSize / 4;
	Vector3 newNodeMax = n->getBrotherComponent<Transform>()->getPosition() + nodeSize / 4;

	//Check AABB
	Vector3 actualPos = getBrotherComponent<Transform>()->getPosition();
	if (actualPos.x > newNodeMin.x && actualPos.x < newNodeMax.x && actualPos.z > newNodeMin.z && actualPos.z < newNodeMax.z)
		return true;
	return false;
}
void NPC::moveToNode(Node* n, int deltaTime)
{
	Transform* trans = getBrotherComponent<Transform>();
	Transform* nextTrans = n->getBrotherComponent<Transform>();

	//Vector unitario de la dirección
	Vector3 delta = (nextTrans->getPosition() - trans->getPosition());
	delta.normalise();
	//Lo multiplicamos por el deltaTime y la velocidad del NPC
	delta = delta * speed_ * ((float)deltaTime / 10);
	delta.y = 0;//We dont want to move in that axis

	//Lo movemos
	trans->translate(delta);

	//Update current node
	if (isInNode(n))
	{
		prevNode_ = node_;
		nextNode_ = nullptr;
		setNode(n);
	}
}

void NPC::changeStat(Stat & stat, float incr)
{
	//Para ajustarlo a la stat en cuestión
	incr /= stat.MAX_VALUE;

	//Le quitamos el icremento y comprobamos límites
	stat.value_ += incr;
	if (stat.decreases_ && stat.value_ < 0)
		stat.value_ = 0;
	else if (!stat.decreases_ && stat.value_ > stat.MAX_VALUE)
		stat.value_ = stat.MAX_VALUE;
}
