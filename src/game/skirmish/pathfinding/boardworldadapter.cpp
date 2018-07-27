#include "game/skirmish/pathfinding/boardworldadapter.hpp"

#include "engine/board.hpp"

namespace qrw
{
const std::array<const Coordinates,4> BoardWorldAdapter::directions_({
	Coordinates(-1,  0),
	Coordinates( 0, -1),
	Coordinates(+1,  0),
	Coordinates( 0, +1)
});

BoardWorldAdapter::BoardWorldAdapter(const Board& board)
	: board_(board)
{
}

bool BoardWorldAdapter::isAccessible(const Coordinates& location) const
{
	return board_.isOnBoard(location) && !board_.isUnitAt(location);
}

std::vector<Coordinates> BoardWorldAdapter::getNeighborLocationsFor(const Coordinates& location) const
{
	return {
		location + directions_[0],
		location + directions_[1],
		location + directions_[2],
		location + directions_[3]
	};
}

} // namespace qrw
