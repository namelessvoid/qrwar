#include "game/skirmish/pathfinding/boardworldadapter.hpp"

#include "engine/board.hpp"

#include "game/skirmish/structure.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/stairs.hpp"
#include "game/skirmish/directions.hpp"

namespace qrw
{

struct StructureAccessibilityDecisionTree
{
	bool plainToPlainAccess() { return true; }
	bool plainToStairsAccess(const Coordinates& plainPosition, const Stairs& stairs) { return stairs.getPosition() + stairs.getFace() != plainPosition; }
	bool plainToWallAccess() { return false; }

	bool stairsToStairsAccess() { return false; }
	bool stairsToWallAccess(const Stairs& stairs, const Wall& wall) { return wall.getPosition() - stairs.getPosition() == stairs.getFace(); }

	bool wallToWallAccess() { return true; }

	bool isAccessible(const Coordinates& position1, const Coordinates& position2, const Board& board)
	{
		Structure* structure1 = board.getStructure(position1);
		Structure* structure2 = board.getStructure(position2);

		if (!structure1)
		{
			if (!structure2)
			{
				return plainToPlainAccess();
			}
			else if (auto stairs2 = dynamic_cast<const Stairs*>(structure2))
			{
				return plainToStairsAccess(position1, *stairs2);
			}
			else if (auto wall2 = dynamic_cast<const Wall*>(structure2))
			{
				return plainToWallAccess();
			}
		}
		else if (auto stairs1 = dynamic_cast<const Stairs*>(structure1))
		{
			if (!structure2)
			{
				return plainToStairsAccess(position2, *stairs1);
			}
			else if (auto stairs2 = dynamic_cast<const Stairs*>(structure2))
			{
				return stairsToStairsAccess();
			}
			else if (auto wall2 = dynamic_cast<const Wall*>(structure2))
			{
				return stairsToWallAccess(*stairs1, *wall2);
			}
		}
		else if (auto wall1 = dynamic_cast<const Wall*>(structure1))
		{
			if (!structure2)
			{
				return plainToWallAccess();
			}
			else if (auto stairs2 = dynamic_cast<const Stairs*>(structure2))
			{
				return stairsToWallAccess(*stairs2, *wall1);
			}
			else if (auto wall2 = dynamic_cast<const Wall*>(structure2))
			{
				return wallToWallAccess();
			}
		}

		return true;
	}
};

BoardWorldAdapter::BoardWorldAdapter(const Board& board)
	: board_(board)
{
}

bool BoardWorldAdapter::isAccessibleFrom(const Coordinates& position1, const Coordinates& position2) const
{
	if(!board_.isOnBoard(position2)) return false;
	if(board_.isUnitAt(position2)) return false;

	StructureAccessibilityDecisionTree structureAccesibilityDecisionTree;
	return structureAccesibilityDecisionTree.isAccessible(position1, position2, board_);
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
