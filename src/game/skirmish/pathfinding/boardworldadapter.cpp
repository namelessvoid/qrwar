#include "game/skirmish/pathfinding/boardworldadapter.hpp"

#include "engine/board.hpp"

#include "game/skirmish/structure.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/directions.hpp"
#include "game/skirmish/imakewallaccessible.hpp"

namespace qrw
{

struct StructureAccessibilityDecisionTree
{
	bool plainToPlain() { return true; }
	bool plainToWallAccess(const Coordinates& plainPosition, const IMakeWallAccessible& wallAccess) { return wallAccess.getPosition() + wallAccess.getFace() != plainPosition; }
	bool plainToWall() { return false; }

	bool wallAccessToWallAccess() { return true; }
	bool wallAccessToWall(const IMakeWallAccessible& wallAccess, const Wall& wall) { return wall.getPosition() - wallAccess.getPosition() == wallAccess.getFace(); }

	bool wallToWall() { return true; }

	bool isAccessible(const Coordinates& position1, const Coordinates& position2, const Board& board)
	{
		Structure* structure1 = board.getStructure(position1);
		Structure* structure2 = board.getStructure(position2);

		if (!structure1)
		{
			if (!structure2)
			{
				return plainToPlain();
			}
			else if (auto wallAccess2 = dynamic_cast<const IMakeWallAccessible*>(structure2))
			{
				return plainToWallAccess(position1, *wallAccess2);
			}
			else if (dynamic_cast<const Wall*>(structure2))
			{
				return plainToWall();
			}
		}
		else if (auto wallAccess1 = dynamic_cast<const IMakeWallAccessible*>(structure1))
		{
			if (!structure2)
			{
				return plainToWallAccess(position2, *wallAccess1);
			}
			else if (dynamic_cast<const IMakeWallAccessible*>(structure2))
			{
				return wallAccessToWallAccess();
			}
			else if (auto wall2 = dynamic_cast<const Wall*>(structure2))
			{
				return wallAccessToWall(*wallAccess1, *wall2);
			}
		}
		else if (auto wall1 = dynamic_cast<const Wall*>(structure1))
		{
			if (!structure2)
			{
				return plainToWall();
			}
			else if (auto wallAccess2 = dynamic_cast<const IMakeWallAccessible*>(structure2))
			{
				return wallAccessToWall(*wallAccess2, *wall1);
			}
			else if (dynamic_cast<const Wall*>(structure2))
			{
				return wallToWall();
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

	StructureAccessibilityDecisionTree structureAccessibilityDecisionTree;
	return structureAccessibilityDecisionTree.isAccessible(position1, position2, board_);
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
