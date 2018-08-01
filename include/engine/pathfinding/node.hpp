#ifndef QRW_PATHFINDING_NODE_HPP
#define QRW_PATHFINDING_NODE_HPP

#include "game/skirmish/coordinates.hpp"

namespace qrw
{
namespace pathfinding
{

template<class TSpatialRepresentation>
class Node
{
	public:
		explicit Node(const TSpatialRepresentation& location)
			: location_(location),
			  parent_(nullptr),
			  g_(0),
			  h_(0)
		{}

		TSpatialRepresentation getLocation() const { return location_; }

		inline void setParent(Node<TSpatialRepresentation>* parent) { parent_ = parent; }

		inline Node<TSpatialRepresentation>* getParent() const { return parent_; }

		inline void setG(int g) { g_ = g; }
		inline int getG() { return g_; }

		inline void setH(int h) { h_ = h; }

		inline int getF() { return this->getG() + h_; }

	private:
		TSpatialRepresentation location_;

		Node<TSpatialRepresentation>* parent_;

		int g_;
		int h_;
};

} // namespace pathfinding
} // namespace qrw

#endif // QRW_PATHFINDING_NODE_HPP
