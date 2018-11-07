#include "game/skirmish/pathfinding/boardworldadapter.hpp"

#include "engine/board.hpp"

#include "game/skirmish/structureaccessibilitychecker.hpp"

namespace qrw
{

BoardWorldAdapter::BoardWorldAdapter(const Board& board)
	: board_(board)
{
}

bool BoardWorldAdapter::isAccessibleFrom(const Coordinates& position1, const Coordinates& position2) const
{
	if(!board_.isOnBoard(position2)) return false;
	if(board_.isUnitAt(position2)) return false;

	StructureAccessibilityChecker structureAccessibilityChecker;
	return structureAccessibilityChecker.isAccessible(position1, position2, board_);
}

std::vector<Coordinates> BoardWorldAdapter::getNeighborLocationsFor(const Coordinates& location) const
{
	return {
		location + Directions::NORTH,
		location + Directions::EAST,
		location + Directions::SOUTH,
		location + Directions::WEST
	};
}

} // namespace qrw
