#include "Node.h"

Node::Node() : posMatrix_({0, 0}), nodeType_(EMPTY)
{
}

Node::~Node()
{
}

void Node::load(json file)
{
	//json type = file["nodeType"];
	nodeType_ = EMPTY;
}

Vector2 Node::getMatrixPos()
{
	return posMatrix_;
}

NodeType Node::getType()
{
	return nodeType_;
}

void Node::setType(NodeType t)
{
	nodeType_ = t;
}
