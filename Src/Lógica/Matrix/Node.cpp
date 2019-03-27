#include "Node.h"

Node::Node() : posMatrix_({0, 0}), nodeType_(EMPTY)
{
}

Node::~Node()
{
}

void Node::load(json file)
{
	json size = file["dimensions"];
	size_.x = size["x"];
	size_.y = size["y"];
	size_.z = size["z"];

	json type = file["nodeType"];
	nodeType_ = EMPTY;
}

Ogre::Vector2 Node::getMatrixPos()
{
	return posMatrix_;
}

Ogre::Vector3 Node::getNodeSize()
{
	return size_;
}

NodeType Node::getType()
{
	return nodeType_;
}

void Node::setType(NodeType t)
{
	nodeType_ = t;
}
