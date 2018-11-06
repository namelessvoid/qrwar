#include "game/constants.hpp"
#include "game/skirmish/imakewallaccessible.hpp"

namespace qrw
{

IMakeWallAccessible::IMakeWallAccessible()
	: face_(Directions::NORTH)
{
	spriteComponent_->setOrigin(0.5f * SQUARE_DIMENSION, 0.5f * SQUARE_DIMENSION);
}

void IMakeWallAccessible::computeTexture()
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

void IMakeWallAccessible::rotate()
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

void IMakeWallAccessible::setFace(const qrw::Coordinates& face)
{
	face_ = face;
	computeTexture();
	qrw::Structure::updateNeighborTextures();
}

void IMakeWallAccessible::setPosition(const Coordinates& position)
{
	position_ = position;
	spriteComponent_->setPosition({SQUARE_DIMENSION * (0.5f + position.getX()), SQUARE_DIMENSION * (0.5f + position.getY())});
}

} // namespace qrw