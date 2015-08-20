#include "engine/pathfinding/node.hpp"

namespace qrw
{
	Node::Node(int x, int y)
	 :	Coordinates(x, y),
		_parent(0)
	{}

	Node::Node(const Coordinates& coordinates)
	 :	Node(coordinates.getX(), coordinates.getY())
	{}

	void Node::setParent(Node* parent)
	{
		this->_parent = parent;
	}

	Node* Node::getParent()
	{
		return _parent;
	}

	void Node::setG(int g)
	{
		this->_g = g;
	}

	int Node::getG()
	{
		return _g;
	}

	void Node::setH(int h)
	{
		this->_h = h;
	}

	int Node::getF()
	{
		return this->getG() + _h;
	}
}
