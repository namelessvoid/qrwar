#ifndef QRW_PATHFINDING_NODE_HPP
#define QRW_PATHFINDING_NODE_HPP

#include "engine/coordinates.hpp"

namespace qrw
{
namespace pathfinding
{

class Node : public qrw::Coordinates
{
	public:
		Node(int x, int y);
		Node(const Coordinates& coordinates);

		void setParent(Node* parent);
		Node* getParent();

		void setG(int g);
		int getG();

		void setH(int h);

		int getF();

	private:
		Node* parent_;

		int g_;
		int h_;
};

} // namespace pathfinding
} // namespace qrw

#endif // QRW_PATHFINDING_NODE_HPP
