#include "Node.h"

Node::Node() : posMatrix_({0, 0}), nodeType_("Empty")
{
}

Node::~Node()
{
}

void Node::load(json file)
{
	//json type = file["nodeType"];
	nodeType_ = "Empty";
}

void Node::setMatrixPos(int i, int j)
{
	posMatrix_ = Ogre::Vector2(i, j);
}

Vector2 Node::getMatrixPos()
{
	return posMatrix_;
}

string Node::getType()
{
	return nodeType_;
}

void Node::setType(string t)
{
	nodeType_ = t;
}
