#include "game/skirmish/wallaccessstructurebase.hpp"

#include "game/constants.hpp"
#include "game/skirmish/isometricconversion.hpp"

namespace qrw
{

WallAccessStructureBase::WallAccessStructureBase()
	: face_(Directions::NORTH)
{
	spriteComponent_->setOrigin(0.5f * SQUARE_DIMENSION, 0.5f * SQUARE_DIMENSION);
}

void WallAccessStructureBase::computeTexture()
{
	float rotation = 0;
	if(face_ == qrw::Directions::EAST)
		rotation = 90;
	else if(face_ == qrw::Directions::SOUTH)
		rotation = 180;
	else if(face_ == qrw::Directions::WEST)
		rotation = 270;

	spriteComponent_->setRotation(rotation);
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

	computeTexture();
	qrw::Structure::updateNeighborTextures();
}

void WallAccessStructureBase::setFace(const qrw::Coordinates& face)
{
	face_ = face;
	computeTexture();
	qrw::Structure::updateNeighborTextures();
}

void WallAccessStructureBase::setPosition(const Coordinates& position)
{
	position_ = position;
	spriteComponent_->setPosition(
		worldToIso({SQUARE_DIMENSION * (0.5f + position.getX()), SQUARE_DIMENSION * (0.5f + position.getY())}
	));
}

} // namespace qrw