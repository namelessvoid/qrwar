#include "game/skirmish/wallaccessstructurebase.hpp"

#include "game/constants.hpp"
#include "game/skirmish/isometricconversion.hpp"

namespace qrw
{

WallAccessStructureBase::WallAccessStructureBase()
	: face_(Directions::NORTH)
{
	spriteComponent_->setOrigin(SQUARE_DIMENSION, 0.5f * SQUARE_DIMENSION);
}

void WallAccessStructureBase::computeTexture()
{
	sf::Vector2f scale(1, 1);
	if(face_ == qrw::Directions::EAST)
		scale = sf::Vector2f(1, -1);
	else if(face_ == qrw::Directions::SOUTH)
		scale = sf::Vector2f(-1, -1);
	else if(face_ == qrw::Directions::WEST)
		scale = sf::Vector2f(-1, 1);

	spriteComponent_->setScale(scale);
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