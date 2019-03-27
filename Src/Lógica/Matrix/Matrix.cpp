#include "Matrix.h"
Matrix::Matrix()
	: mSize_({ 0 ,0 }), nSize_({0, 0, 0}), matrix_(mSize_.y, vector<Entity*>(mSize_.x, nullptr))
{
}

Matrix::~Matrix()
{
	for (int i = 0; i < matrix_.size(); i++) {
		for (int j = 0; j < matrix_[0].size(); j++)
			delete matrix_[i][j];
	}
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

	dirs_ = { { 1,0 }, { -1,0 }, { 0,1 }, { 0, -1 } };

	matrix_ = M(mSize_.y, vector<Entity*>(mSize_.x, nullptr));
	createMatrix();
}

void Matrix::start()
{
	for (Component* c : comps)
		if (c->isActive())
			c->start();
}

void Matrix::render(unsigned int time)
{
	for (Component* c : comps)
		if (c->isActive())
			c->render(time);
}

void Matrix::update(unsigned int time)
{
	for (Component* c : comps)
		if (c->isActive())
			c->update(time);
}

void Matrix::createMatrix()
{
	Vector3 posIni = getPosIni();
	for (int j = 0; j < mSize_.y; j++) {
		for (int i = 0; i < mSize_.x; i++) {
			Entity* e = EntityFactory::Instance()->createEntityFromBlueprint("Node");
			e->getComponent<Transform>()->setPosition({ (Ogre::Real)(posIni.x + (i * nSize_.x)), (Ogre::Real)posIni.y, (Ogre::Real)(posIni.z + (j * nSize_.z)) });
			e->getComponent<MeshRenderer>()->start();
			for (Component* c : e->getComponents())
				comps.push_back(c);

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

M Matrix::getMatrix()
{
	return matrix_;
}

Entity * Matrix::getEntityNode(int i, int j)
{
	return matrix_[i][j];
}

list<Entity*> Matrix::getAdj(Entity* e)
{
	list<Entity*> list;
	Vector2 nPos = e->getComponent<Node>()->getMatrixPos();
	for (pair<int, int> p : dirs_) {
		if (limits(nPos.x + p.first, nPos.y + p.second))
			list.push_back(getEntityNode(nPos.x + p.first, nPos.y + p.second));
	}

	return list;
}

list<Entity*> Matrix::getAdj(int i, int j)
{
	list<Entity*> list;
	for (pair<int, int> p : dirs_) {
		if (limits(i + p.first, j + p.second))
			list.push_back(getEntityNode(i + p.first, j + p.second));
	}

	return list;
}


bool Matrix::limits(int i, int j)
{
	return i > 0 && j > 0 && i < mSize_.x, j < mSize_.y;
}
