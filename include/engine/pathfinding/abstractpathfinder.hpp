#ifndef QRW_PATHFINDING_ABSTRACTALGORITHM_HPP
#define QRW_PATHFINDING_ABSTRACTALGORITHM_HPP

namespace qrw
{
class Board;
class Coordinates;

namespace pathfinding
{

class Path;

class AbstractPathfinder
{
	public:
		virtual ~AbstractPathfinder() {}

		virtual void setBoard(Board* board) = 0;
		virtual Path* findPath(const Coordinates& start, const Coordinates& end) = 0;
};

} // namespace pathfinding
} // namespace qrw

#endif // QRW_PATHFINDING_ABSTRACTALGORITHM_HPP
