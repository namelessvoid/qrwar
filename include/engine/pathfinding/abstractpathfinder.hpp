#ifndef QRW_PATHFINDING_ABSTRACTALGORITHM_HPP
#define QRW_PATHFINDING_ABSTRACTALGORITHM_HPP

#include "iworldadapter.hpp"

namespace qrw
{
class Board;
class Coordinates;

namespace pathfinding
{

class Path;

template<class TSpatialRepresentation>
class AbstractPathfinder
{
public:
	virtual ~AbstractPathfinder() = default;

	void setWorldAdapter(const IWorldAdapter<TSpatialRepresentation>& worldAdapter) { worldAdapter_ = &worldAdapter; }
	virtual Path* findPath(const TSpatialRepresentation& start, const TSpatialRepresentation& end) = 0;

protected:
	const IWorldAdapter<TSpatialRepresentation>* worldAdapter_;
};

} // namespace pathfinding
} // namespace qrw

#endif // QRW_PATHFINDING_ABSTRACTALGORITHM_HPP
