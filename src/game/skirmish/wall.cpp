#include "game/skirmish/wall.hpp"

#include "game/constants.hpp"
#include "game/skirmish/stairs.hpp"
#include "game/skirmish/directions.hpp"
#include "game/skirmish/isometricconversion.hpp"

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
	eastWallSprite_ = new SpriteComponent(RENDER_LAYER_GAME);
	eastWallSprite_->setSize({SQUARE_DIMENSION, 2.5f * SQUARE_DIMENSION});
	eastWallSprite_->setOrigin(0, 1.5f * SQUARE_DIMENSION);
	eastWallSprite_->setTexture(TextureManager::getInstance()->getTexture("wall_east"));
	addComponent(eastWallSprite_);

	southWallSprite_ = new SpriteComponent(RENDER_LAYER_GAME);
	southWallSprite_->setSize({SQUARE_DIMENSION, 2.5f * SQUARE_DIMENSION});
	southWallSprite_->setOrigin(SQUARE_DIMENSION, 1.5f * SQUARE_DIMENSION);
	southWallSprite_->setTexture(TextureManager::getInstance()->getTexture("wall_south"));
	addComponent(southWallSprite_);

	topFloorSprite_ = new SpriteComponent(RENDER_LAYER_GAME);
	topFloorSprite_->setSize({2.0f * SQUARE_DIMENSION, SQUARE_DIMENSION});
	topFloorSprite_->setOrigin(SQUARE_DIMENSION, 0.5f * SQUARE_DIMENSION);
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

void Wall::update(float elapsedTimeInSeconds)
{
	GameObject::update(elapsedTimeInSeconds);

	bool makeTransparent = false;
	if(auto board = g_scene.findSingleGameObject<Board>())
	{
		makeTransparent = blocksVisibilityOn(getPosition() + Coordinates(-1, -1), *board)
				|| blocksVisibilityOn(getPosition() + Coordinates(-2, -2), *board)
				|| blocksVisibilityOn(getPosition() + Coordinates(0, -1), *board)
				|| blocksVisibilityOn(getPosition() + Coordinates(-1, -2), *board)
				|| blocksVisibilityOn(getPosition() + Coordinates(-1, 0), *board)
				|| blocksVisibilityOn(getPosition() + Coordinates(-2, -1), *board);
	}

	sf::Color color = makeTransparent ? sf::Color(255, 255, 255, 128) : sf::Color::White;
	southWallSprite_->setFillColor(color);
	eastWallSprite_->setFillColor(color);
}

bool Wall::blocksVisibilityOn(const Coordinates& position, const Board& board)
{
	if(board.isTerrainAt(position)) return true;
	if(board.isUnitAt(position)) return true;

	if(auto structure = board.getStructure(position))
	{
		return dynamic_cast<Wall*>(structure) == nullptr;
	}

	return false;
}

void Wall::setPosition(const Coordinates& position)
{
	Structure::setPosition(position);

	sf::Vector2f isometricPosition = worldToIso({SQUARE_DIMENSION * position_.getX(), SQUARE_DIMENSION * position.getY()});
	eastWallSprite_->setPosition(isometricPosition);
	southWallSprite_->setPosition(isometricPosition);
	topFloorSprite_->setPosition(isometricPosition - sf::Vector2f(0, 1.5f * SQUARE_DIMENSION));
}

const sf::Texture* Wall::getTexture() const
{
	return TextureManager::getInstance()->getTexture("wall_south");
}

}