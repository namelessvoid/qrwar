#include "game/skirmish/wall.hpp"

#include "game/constants.hpp"
#include "game/skirmish/stairs.hpp"
#include "game/skirmish/directions.hpp"
#include "game/skirmish/isometricconversion.hpp"
#include "game/skirmish/boardtoworldconversion.hpp"

#include "gui/scene.hpp"
#include "gui/texturemanager.hpp"
#include "engine/board.hpp"
#include "foundation/spritecomponent.hpp"

#include "game/renderlayers.hpp"

namespace qrw
{

SID Wall::typeName("qrw::Wall");

Wall::Wall()
  : Structure()
{
	eastWallSprite_ = new SpriteComponent(*this, RENDER_LAYER_GAME);
	eastWallSprite_->setSize({SQUARE_DIMENSION, 2.5f * SQUARE_DIMENSION});
	eastWallSprite_->setOrigin(0, 1.5f * SQUARE_DIMENSION);
	eastWallSprite_->setTexture(TextureManager::getInstance()->getTexture("wall_east"));
	addComponent(eastWallSprite_);

	southWallSprite_ = new SpriteComponent(*this, RENDER_LAYER_GAME);
	southWallSprite_->setSize({SQUARE_DIMENSION, 2.5f * SQUARE_DIMENSION});
	southWallSprite_->setOrigin(SQUARE_DIMENSION, 1.5f * SQUARE_DIMENSION);
	southWallSprite_->setTexture(TextureManager::getInstance()->getTexture("wall_south"));
	addComponent(southWallSprite_);

	topFloorSprite_ = new SpriteComponent(*this, RENDER_LAYER_GAME);
	topFloorSprite_->setSize({2.0f * SQUARE_DIMENSION, SQUARE_DIMENSION});
	topFloorSprite_->setOrigin(SQUARE_DIMENSION, 0.0f);
	topFloorSprite_->setTexture(TextureManager::getInstance()->getTexture("wall_top"));
	addComponent(topFloorSprite_);
}

bool Wall::isConnectedTo(const Coordinates& direction, const Board& board) const
{
	Coordinates neighborPosition = position_ + direction;
	Structure* structure = board.getStructure(neighborPosition);

	if(!structure) return false;

	if(dynamic_cast<Wall*>(structure))
		return true;
	else if(auto stairs = dynamic_cast<Stairs*>(structure))
	{
		if(stairs->getFace() == position_ - stairs->getPosition())
			return true;
	}

	return false;
}

void Wall::setPosition(const Coordinates& position)
{
	Structure::setPosition(position);
	updateSprites();
}

const sf::Texture* Wall::getTexture() const
{
	return TextureManager::getInstance()->getTexture("wall_south");
}

void Wall::flatModeChanged()
{
	updateSprites();
}

void Wall::updateSprites()
{
	sf::Vector2f isometricPosition = worldToIso(boardToWorld(position_));

	eastWallSprite_->setPosition(isometricPosition);
	eastWallSprite_->setVisible(!isFlatMode());

	southWallSprite_->setPosition(isometricPosition);
	southWallSprite_->setVisible(!isFlatMode());

	topFloorSprite_->setPosition(isometricPosition - sf::Vector2f(0, (float)(!isFlatMode()) * 2.0f * SQUARE_DIMENSION));
	topFloorSprite_->setZIndex(isometricPosition.y);
}


}