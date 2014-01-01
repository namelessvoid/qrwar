#include "engine/pathfinding/node.hpp"

namespace qrw
{
	Node::Node(int x, int y)
	 :	Coordinates(x, y),
	 	parent(0)
	{}

	Node::Node(const Coordinates& coordinates)
	 :	Node(coordinates.getX(), coordinates.getY())
	{}

	void Node::setParent(Node* parent)
	{
		this->parent = parent;
	}

	Node* Node::getParent()
	{
		return parent;
	}

	void Node::setG(int g)
	{
		this->g = g;
	}

	int Node::getG()
	{
		return g;
	}

	void Node::setH(int h)
	{
		this->h = h;
	}

	int Node::getF()
	{
		return this->getG() + h;
	}
}
