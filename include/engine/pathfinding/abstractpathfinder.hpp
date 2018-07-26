#ifndef QRW_PATHFINDING_ABSTRACTALGORITHM_HPP
#define QRW_PATHFINDING_ABSTRACTALGORITHM_HPP

namespace qrw
{
class Board;
class Coordinates;

namespace pathfinding
{

class Path;

template<class TWorldAdapter, class TSpatialRepresentation>
class AbstractPathfinder
{
public:
	virtual ~AbstractPathfinder() = default;

	virtual void setWorldAdapter(const TWorldAdapter& worldAdapter) { worldAdapter_ = &worldAdapter; }
	virtual Path* findPath(const TSpatialRepresentation& start, const TSpatialRepresentation& end) = 0;

protected:
	const TWorldAdapter* worldAdapter_;
};

} // namespace pathfinding
} // namespace qrw

#endif // QRW_PATHFINDING_ABSTRACTALGORITHM_HPP
