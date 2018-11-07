#include "game/skirmish/structureaccessibilitychecker.hpp"

namespace qrw
{

bool StructureAccessibilityChecker::isAccessible(const Coordinates& position1, const Coordinates& position2,
												 const Board& board)
{
	Structure* structure1 = board.getStructure(position1);
	Structure* structure2 = board.getStructure(position2);

	if (!structure1) {
		if (!structure2) {
			return plainToPlain();
		} else if (auto wallAccess2 = dynamic_cast<const WallAccessStructureBase*>(structure2)) {
			return plainToWallAccess(position1, *wallAccess2);
		} else if (dynamic_cast<const Wall*>(structure2)) {
			return plainToWall();
		}
	} else if (auto wallAccess1 = dynamic_cast<const WallAccessStructureBase*>(structure1)) {
		if (!structure2) {
			return plainToWallAccess(position2, *wallAccess1);
		} else if (dynamic_cast<const WallAccessStructureBase*>(structure2)) {
			return wallAccessToWallAccess();
		} else if (auto wall2 = dynamic_cast<const Wall*>(structure2)) {
			return wallAccessToWall(*wallAccess1, *wall2);
		}
	} else if (auto wall1 = dynamic_cast<const Wall*>(structure1)) {
		if (!structure2) {
			return plainToWall();
		} else if (auto wallAccess2 = dynamic_cast<const WallAccessStructureBase*>(structure2)) {
			return wallAccessToWall(*wallAccess2, *wall1);
		} else if (dynamic_cast<const Wall*>(structure2)) {
			return wallToWall();
		}
	}

	return true;
}

bool StructureAccessibilityChecker::plainToPlain()
{
	return true;
}

bool StructureAccessibilityChecker::plainToWallAccess(const Coordinates& plainPosition,
													  const WallAccessStructureBase& wallAccess)
{
	return wallAccess.getPosition() + wallAccess.getFace() != plainPosition;
}

bool StructureAccessibilityChecker::plainToWall()
{
	return false;
}

bool StructureAccessibilityChecker::wallAccessToWallAccess()
{
	return true;
}

bool StructureAccessibilityChecker::wallAccessToWall(const WallAccessStructureBase& wallAccess, const Wall& wall)
{
	return wall.getPosition() - wallAccess.getPosition() == wallAccess.getFace();
}

bool StructureAccessibilityChecker::wallToWall()
{
	return true;
}

} // namespace qrw
