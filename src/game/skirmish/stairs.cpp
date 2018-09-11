#include "game/skirmish/stairs.hpp"

#include "gui/texturemanager.hpp"
#include "foundation/spritecomponent.hpp"
#include "game/constants.hpp"

namespace qrw
{

SID Stairs::typeName("qrw::Stairs");

Stairs::Stairs()
	: face_(Directions::NORTH)
{
	spriteComponent_->setTexture(TextureManager::getInstance()->getTexture("stairs"));
	spriteComponent_->setOrigin(0.5f * SQUARE_DIMENSION, 0.5f * SQUARE_DIMENSION);
}

void Stairs::computeTexture()
{
	float rotation = 0;
	if(face_ == Directions::EAST)
		rotation = 90;//texture = TextureManager::getInstance()->getTexture("wallE");
	else if(face_ == Directions::SOUTH)
		rotation = 180;//texture = TextureManager::getInstance()->getTexture("wallS");
	else if(face_ == Directions::WEST)
		rotation = 270;//texture = TextureManager::getInstance()->getTexture("wallW");

	spriteComponent_->setRotation(rotation);
}

void Stairs::rotate()
{
	if(face_ == Directions::NORTH)
		face_ = Directions::EAST;
	else if(face_ == Directions::EAST)
		face_ = Directions::SOUTH;
	else if(face_ == Directions::SOUTH)
		face_ = Directions::WEST;
	else if(face_ == Directions::WEST)
		face_ = Directions::NORTH;

	computeTexture();
	updateNeighborTextures();
}

void Stairs::setPosition(const Coordinates& position)
{
	position_ = position;
	spriteComponent_->setPosition({SQUARE_DIMENSION * (0.5f + position.getX()), SQUARE_DIMENSION * (0.5f + position.getY())});
}

}