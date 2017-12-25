#include "engine/pathfinding/node.hpp"

namespace qrw
{
namespace pathfinding
{

Node::Node(int x, int y)
 :	Coordinates(x, y),
	parent_(0)
{}

Node::Node(const Coordinates& coordinates)
 :	Node(coordinates.getX(), coordinates.getY())
{}

void Node::setParent(Node* parent)
{
	this->parent_ = parent;
}

Node* Node::getParent()
{
	return parent_;
}

void Node::setG(int g)
{
	this->g_ = g;
}

int Node::getG()
{
	return g_;
}

void Node::setH(int h)
{
	this->h_ = h;
}

int Node::getF()
{
	return this->getG() + h_;
}

} // namespace pathfinding
} // namespace qrw
