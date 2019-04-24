#include "ConstructionMode.h"

#include "PARKEngine/SceneManager.h"
#include "PARKEngine/InputManager.h"
#include "PARKEngine/OgreManager.h"
#include "PARKEngine/Entity.h"
#include "PARKEngine/Transform.h"
#include "PARKEngine/MeshRenderer.h"
#include "Matrix/Matrix.h"
#include "Matrix/Node.h"
#include <string>
#include "Edificio.h"

ConstructionMode::ConstructionMode() : matrixEntity_(nullptr), nodeEntity_(nullptr), buildingEntity_(nullptr), canConst_(false), constructActive_(false)
{
}

ConstructionMode::~ConstructionMode()
{
}

void ConstructionMode::load(json file)
{
	
	for (json b : file["BuildingsNames"]){
		buildingTypes_.push_back(b["name"]);
	}

}

void ConstructionMode::start()
{
	matrixEntity_ = SceneManager::instance()->currentState()->getEntity("Matrix");
}

void ConstructionMode::update(unsigned int time)
{
	if (constructActive_) {
		pair<Entity*, Ogre::Vector3> nodeAndPos= OgreManager::instance()->raycastToMouse();
		if (nodeAndPos.first != nullptr && nodeAndPos.first->getComponent<Node>() != nullptr) {
			nodes_ = getNodesToConstruct(nodeAndPos.first, nodeAndPos.second);
			canConst_ = canConstruct(build_->getTam().x * build_->getTam().x);
			setNodeMaterial(true, canConst_);
		}
	}
}

bool ConstructionMode::handleEvent(unsigned int time)
{
	if (InputManager::getSingletonPtr()->isKeyDown("ConstructBuilding"))
	{
		if (canConst_) {
			setBuilding();
			matrixEntity_->getComponent<Matrix>()->getInfo();
		}
	}
	if (InputManager::getSingletonPtr()->isKeyDown("ExitConstruct")) {
		constructActive_ = false;
		canConst_ = false;
		setNodeMaterial(false, true);
	}

	return false;
}

void ConstructionMode::buildInMatrix(int i, int j, std::string name)
{
	//Contruye
	Matrix* m = matrixEntity_->getComponent<Matrix>();
	buildingEntity_ = EntityFactory::Instance()->createEntityFromBlueprint(name);
	SceneManager::instance()->currentState()->addEntity(buildingEntity_);
	build_ = buildingEntity_->getComponent<Edificio>();

	// Posicion espacial
	int x = 0, z = 0;
	x = (j * m->getNodeSize().x) - (m->getMatrix().size() / 2 * m->getNodeSize().x);
	z = (i * m->getNodeSize().z) - (m->getMatrix()[0].size() / 2 * m->getNodeSize().z);

	x += (build_->getTamX() * matrixEntity_->getComponent<Matrix>()->getNodeSize().x) / 2 - (matrixEntity_->getComponent<Matrix>()->getNodeSize().x / 2);
	z += (build_->getTamY() * matrixEntity_->getComponent<Matrix>()->getNodeSize().z) / 2 - (matrixEntity_->getComponent<Matrix>()->getNodeSize().z / 2);

	buildingEntity_->getComponent<Transform>()->setPosition(Ogre::Vector3(x, build_->getHeight(), z));
	buildingEntity_->getComponent<MeshRenderer>()->start();

	//Modificar el tipo de nodos de la matriz
	for (int x = i; x < build_->getTamX() + i; x++) {
		for (int z = j; z < build_->getTamY() + j; z++) {
			m->getEntityNode(x, z)->getComponent<Node>()->setType(name);
		}
	}

	// Poner la entrada y la salida
	if (build_->getBuildingName() != "Road") setEntryExit();

}


void ConstructionMode::construct(string bName)
{
	constructActive_ = true;
	buildingEntity_ = EntityFactory::Instance()->createEntityFromBlueprint(bName);
	buildingEntity_->getComponent<Transform>()->setPosition(Ogre::Vector3(0, -1000, 0));
	buildingEntity_->getComponent<MeshRenderer>()->start();
	build_ = buildingEntity_->getComponent<Edificio>();
}

list<Entity*> ConstructionMode::getNodesToConstruct(Entity* node, Ogre::Vector3 mousePos)
{
	int maxAdjX = build_->getTamX() / 2, maxAdjY = build_->getTamY() / 2;
	list<Entity*> adj = matrixEntity_->getComponent<Matrix>()->getAdj(node, maxAdjX, maxAdjY);
	Ogre::Vector3 nodeSize = matrixEntity_->getComponent<Matrix>()->getNodeSize();
	Ogre::Vector2 nodeMatrixPos = node->getComponent<Node>()->getMatrixPos();

	if (build_->getTamX() % 2 == 0)
	{
		float x = (abs(mousePos.x) / nodeSize.x) - (int)(abs(mousePos.x) / nodeSize.x);
		if (nodeMatrixPos.y + x > nodeMatrixPos.y + 0.5 && mousePos.x > 0 || nodeMatrixPos.y + x < nodeMatrixPos.y + 0.5 && mousePos.x < 0)
			x = maxAdjX;
		else
			x = -maxAdjX;

		std::list<Entity*>::iterator i = adj.begin();
		while (i != adj.end()) {
			if ((*i)->getComponent<Node>()->getMatrixPos().y - nodeMatrixPos.y == x)
				adj.erase(i++);
			else
				i++;
		}
	}
	if (build_->getTamY() % 2 == 0) {
		float y = (abs(mousePos.z) / nodeSize.z) - (int)(abs(mousePos.z) / nodeSize.z);
		if (nodeMatrixPos.x + y > nodeMatrixPos.x + 0.5 && mousePos.z > 0 || nodeMatrixPos.x + y < nodeMatrixPos.x + 0.5 && mousePos.z < 0)
			y = maxAdjY;
		else
			y = -maxAdjY;

		std::list<Entity*>::iterator i = adj.begin();
		while (i != adj.end()) {
			if ((*i)->getComponent<Node>()->getMatrixPos().x - nodeMatrixPos.x == y)
				adj.erase(i++);
			else
				i++;
		}
	}
	
	return adj;
}

bool ConstructionMode::canConstruct(int n)
{
	if (nodes_.size() < n) return false;
	for (Entity* e : nodes_)
		if (e->getComponent<Node>()->getType() != "Empty")
			return false;

	return true;
}

Ogre::Vector3 ConstructionMode::getPosToConstruct()
{
	int x = numeric_limits<int>::max(), y = 0, z = numeric_limits<int>::max();

	for (Entity* e : nodes_) {
		x = min(x, (int)e->getComponent<Transform>()->getPosition().x);
		z = min(z, (int)e->getComponent<Transform>()->getPosition().z);
	}
	
	y = build_->getHeight();

	x += (build_->getTamX() * matrixEntity_->getComponent<Matrix>()->getNodeSize().x) / 2 - (matrixEntity_->getComponent<Matrix>()->getNodeSize().x / 2);
	z += (build_->getTamY() * matrixEntity_->getComponent<Matrix>()->getNodeSize().z) / 2 - (matrixEntity_->getComponent<Matrix>()->getNodeSize().z / 2);

	return Ogre::Vector3(x, y, z);
}

void ConstructionMode::setNodesType()
{
	for (Entity* e : nodes_) {
		e->getComponent<Node>()->setType(build_->getBuildingName());
	}
}

void ConstructionMode::setBuilding()
{
	bool set = false;
	Ogre::Vector3 pos = getPosToConstruct();

	buildingEntity_->setActive(true);
	buildingEntity_->getComponent<Transform>()->setPosition(Ogre::Vector3(pos.x, pos.y, pos.z));
	buildingEntity_->getComponent<MeshRenderer>()->start();

	setNodesType();
	set = true;
	setNodeMaterial(false, true);
	nodes_.clear();
	canConst_ = false;


	if (build_->getBuildingName() != "Road") {
		setEntryExit();
		constructActive_ = false;
	}
	else {
		construct(build_->getBuildingName());
	}

	SceneManager::instance()->currentState()->addEntity(buildingEntity_);
}

void ConstructionMode::createEntryExitRoad(string roadName)
{
	Entity* e = EntityFactory::Instance()->createEntityFromBlueprint(roadName);
	Ogre::Vector3 posIni = buildingEntity_->getComponent<Transform>()->getPosition();
	Ogre::Vector3 ePos;
	int x = 0, z = 0;
	Matrix* m = matrixEntity_->getComponent<Matrix>();
	if (roadName == "EntryRoad") {
		x = build_->getEntryX() * m->getNodeSize().x + posIni.x;
		z = build_->getEntryY() * m->getNodeSize().z + posIni.z;
	}
	else {
		x = build_->getExitX() * m->getNodeSize().x + posIni.x;
		z = build_->getExitY() * m->getNodeSize().z + posIni.z;
	}

	x -= m->getNodeSize().x / 2;
	z -= m->getNodeSize().z / 2;
	int nX = x / m->getNodeSize().x + m->getMatrix().size() / 2;
	int nZ = z / m->getNodeSize().z + m->getMatrix()[0].size() / 2;
	//Nodo de la matriz
	Node* node = m->getEntityNode(nZ, nX)->getComponent<Node>();
	node->setType(roadName);
	//LO PONGO AQUI PROVISIONALMENTE
	if (roadName == "EntryRoad") build_->setEntryNode(node);
	else build_->setExitNode(node);
	ePos = Ogre::Vector3(x, e->getComponent<Edificio>()->getHeight(), z);
	e->getComponent<Transform>()->setPosition(ePos);
	e->getComponent<MeshRenderer>()->start();

	SceneManager::instance()->currentState()->addEntity(e);
}

void ConstructionMode::setEntryExit()
{
	createEntryExitRoad("EntryRoad");
	createEntryExitRoad("ExitRoad");
}

void ConstructionMode::setNodeMaterial(bool enable, bool can)
{
	MeshRenderer* mesh = nullptr;
	vector<vector<Entity*>> matrix = matrixEntity_->getComponent<Matrix>()->getMatrix();
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			bool isNode = false;
			mesh = matrix[i][j]->getComponent<MeshRenderer>();
			for (Entity* e : nodes_) {
				if (matrix[i][j] == e) isNode = true;
			}
			if (isNode) {
				mesh->setVisible(enable);
				if (enable) can ? mesh->setMaterial("NodeCanConstruct") : mesh->setMaterial("NodeCantConstruct");
			}
			else {
				mesh->setVisible(false);
			}
		}
	}

}


