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
	
	for (json b : file["BuildingsNames"])
	{
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
		pair<Entity*, Ogre::Vector3> nodeAndPos= OgreManager::instance()->raycast();
		if (nodeAndPos.first != nullptr && nodeAndPos.first->getComponent<Node>() != nullptr) {
			nodes_ = getNodesToConstruct(nodeAndPos.first, nodeAndPos.second);
			canConst_ = canConstruct(build_->getTam().x * build_->getTam().x);
			setNodeMaterial(true, canConst_);
		}
	}
}

bool ConstructionMode::handleEvent(unsigned int time)
{
	if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_P))
	{
		construct("Patitos", time);
	}
	else if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_O))
	{
		construct("Burguer", time);
	}
	else if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_I))
	{
		construct("Road", time);
	}
	else if (InputManager::getSingletonPtr()->getKeyboard()->isKeyDown(OIS::KC_Y))
	{
		if (canConst_) {
			setBuilding();
		}
		else
			cout << "No puedes construir" << endl;
	}

	return false;
}

void ConstructionMode::construct(string bName, unsigned int time)
{
	constructActive_ = true;
	buildingEntity_ = EntityFactory::Instance()->createEntityFromBlueprint(bName);
	buildingEntity_->getComponent<Transform>()->setPosition(Ogre::Vector3(0, -1000, 0));
	buildingEntity_->getComponent<MeshRenderer>()->start();
	SceneManager::instance()->currentState()->addEntity(buildingEntity_);
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
		if (nodeMatrixPos.x + x > nodeMatrixPos.x + 0.5 && mousePos.x > 0 || nodeMatrixPos.x + x < nodeMatrixPos.x + 0.5 && mousePos.x < 0)
			x = maxAdjX;
		else
			x = -maxAdjX;

		std::list<Entity*>::iterator i = adj.begin();
		while (i != adj.end()) {
			if ((*i)->getComponent<Node>()->getMatrixPos().x - nodeMatrixPos.x == x)
				adj.erase(i++);
			else
				i++;
		}
	}
	if (build_->getTamY() % 2 == 0) {
		float y = (abs(mousePos.z) / nodeSize.z) - (int)(abs(mousePos.z) / nodeSize.z);
		if (nodeMatrixPos.y + y > nodeMatrixPos.y + 0.5 && mousePos.z > 0 || nodeMatrixPos.y + y < nodeMatrixPos.y + 0.5 && mousePos.z < 0)
			y = -maxAdjY;
		else
			y = maxAdjY;

		std::list<Entity*>::iterator i = adj.begin();
		while (i != adj.end()) {
			if ((*i)->getComponent<Node>()->getMatrixPos().y - nodeMatrixPos.y == y)
				adj.erase(i++);
			else
				i++;
		}
	}

	for (Entity* e : adj) {
		cout << "X: " << e->getComponent<Node>()->getMatrixPos().x << " ";
		cout << "Z: " << e->getComponent<Node>()->getMatrixPos().y << endl;
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

	cout << "X: " << x << " Y: " << y << " Z: " << z << endl;

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
	setNodesType();
	buildingEntity_->setActive(true);
	buildingEntity_->getComponent<Transform>()->setPosition(Ogre::Vector3(pos.x, pos.y, pos.z));
	buildingEntity_->getComponent<MeshRenderer>()->start();
	set = true;
	setNodeMaterial(false, true);
	nodes_.clear();
	canConst_ = false;
	constructActive_ = false;
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


