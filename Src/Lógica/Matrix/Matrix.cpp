#include "Matrix.h"
Matrix::Matrix()
	: mSize_({ 0 ,0 }), nSize_({0, 0, 0})
{
}

Matrix::~Matrix()
{
}


void Matrix::load(json file)
{
	json matrixSize = file["matrixSize"];
	mSize_.x = matrixSize["x"];
	mSize_.y = matrixSize["y"];

	json nodeSize = file["nodeSize"];
	nSize_.x = nodeSize["x"];
	nSize_.y = nodeSize["y"];
	nSize_.z = nodeSize["z"];

	for (int i = 0; i < mSize_.x; i++) {
		matrix_.push_back(vector<Entity*>());
		for (int j = 0; j < mSize_.y; j++) {
			matrix_[i].push_back(nullptr);
		}
	}
	createMatrix();
}

void Matrix::start()
{
	for (int i = 0; i < matrix_.size(); i++) {
		for (int j = 0; j < matrix_[0].size(); j++) {
			SceneManager::instance()->currentState()->addEntity(matrix_[i][j]);
			for (Component* c : matrix_[i][j]->getComponents()) {
				if (c->isActive())
					c->start();
			}
		}
	}
}

void Matrix::createMatrix()
{
	Vector3 posIni = getPosIni();
	for (int j = 0; j < mSize_.y; j++) {
		for (int i = 0; i < mSize_.x; i++) {
			Entity* e = EntityFactory::Instance()->createEntityFromBlueprint("Node");
			e->getComponent<Transform>()->setPosition({ (Ogre::Real)(posIni.x + (i * nSize_.x)), (Ogre::Real)posIni.y, (Ogre::Real)(posIni.z + (j * nSize_.z)) });
			e->getComponent<Node>()->setMatrixPos(i, j);
			matrix_[i][j] = e;
		}
	}
}

Vector3 Matrix::getPosIni()
{
	Vector3 v;
	float midX = mSize_.x / 2;
	float midY = mSize_.y / 2;

	v = Vector3(-midX * nSize_.x, 0.0f, -midY * nSize_.z);
	return v;
}

vector<vector<Entity*>> Matrix::getMatrix()
{
	return matrix_;
}

Entity * Matrix::getEntityNode(int i, int j)
{
	return matrix_[i][j];
}

list<Entity*> Matrix::getAdj(Entity* e, int x, int y)
{
	list<Entity*> list;
	Vector2 nPos = e->getComponent<Node>()->getMatrixPos();
	for (int i = -x; i <= x; i++) {
		for (int j = -y; j <= y; j++) {
			if (limits(nPos.x + i, nPos.y + j)) {
				list.push_back(getEntityNode(nPos.x + i, nPos.y + j));
			}
		}
	}
	return list;
}

Ogre::Vector3 Matrix::getNodeSize()
{
	return nSize_;
}

bool Matrix::limits(int i, int j)
{
	return i >= 0 && j >= 0 && i < mSize_.x && j < mSize_.y;
}
