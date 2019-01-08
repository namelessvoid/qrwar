#include "game/skirmish/wallaccessstructurebase.hpp"

#include "game/constants.hpp"
#include "game/skirmish/isometricconversion.hpp"

namespace qrw
{

WallAccessStructureBase::WallAccessStructureBase()
	: face_(Directions::NORTH)
{
}

void WallAccessStructureBase::rotate()
{
	if(face_ == qrw::Directions::NORTH)
		face_ = qrw::Directions::EAST;
	else if(face_ == qrw::Directions::EAST)
		face_ = qrw::Directions::SOUTH;
	else if(face_ == qrw::Directions::SOUTH)
		face_ = qrw::Directions::WEST;
	else if(face_ == qrw::Directions::WEST)
		face_ = qrw::Directions::NORTH;

	qrw::Structure::updateNeighborTextures();
}

void WallAccessStructureBase::setFace(const qrw::Coordinates& face)
{
	face_ = face;
	computeTexture();
	qrw::Structure::updateNeighborTextures();
}

} // namespace qrw