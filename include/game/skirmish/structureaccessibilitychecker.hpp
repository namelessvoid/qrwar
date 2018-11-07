#ifndef QRW_STRUCTUREACCESSIBILITYCHECKER_HPP
#define QRW_STRUCTUREACCESSIBILITYCHECKER_HPP

#include "game/skirmish/wallaccessstructurebase.hpp"
#include "game/skirmish/wall.hpp"
#include "engine/board.hpp"

namespace qrw
{

struct StructureAccessibilityChecker
{
public:
	bool isAccessible(const Coordinates& position1, const Coordinates& position2, const Board& board);

private:
	bool plainToPlain();

	bool plainToWallAccess(const Coordinates& plainPosition, const WallAccessStructureBase& wallAccess);

	bool plainToWall();

	bool wallAccessToWallAccess();

	bool wallAccessToWall(const WallAccessStructureBase& wallAccess, const Wall& wall);

	bool wallToWall();
};

} //namespace qrw

#endif //QRW_STRUCTUREACCESSIBILITYCHECKER_HPP
