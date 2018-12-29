#include "game/skirmish/wall.hpp"

#include "game/constants.hpp"
#include "game/skirmish/stairs.hpp"
#include "game/skirmish/directions.hpp"

#include "gui/scene.hpp"
#include "gui/texturemanager.hpp"
#include "engine/board.hpp"
#include "foundation/spritecomponent.hpp"

namespace qrw
{

SID Wall::typeName("qrw::Wall");

Wall::Wall()
  : Structure()
{
	spriteComponent_->setSize({2.0f * SQUARE_DIMENSION, 3.0f * SQUARE_DIMENSION});
	spriteComponent_->setOrigin(SQUARE_DIMENSION, 2.0f * SQUARE_DIMENSION);
}

void Wall::computeTexture()
{
	std::string textureName = "wall";
	Board* board = g_scene.findSingleGameObject<Board>();
	if(board)
	{
		if(isConnectedTo(Directions::NORTH, *board))
			textureName += 'N';
		if(isConnectedTo(Directions::EAST, *board))
			textureName += 'O';
		if(isConnectedTo(Directions::SOUTH, *board))
			textureName += 'S';
		if(isConnectedTo(Directions::WEST, *board))
			textureName += 'W';
	}

	spriteComponent_->setTexture(TextureManager::getInstance()->getTexture(textureName));
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

	spriteComponent_->setFillColor(makeTransparent ? sf::Color(255, 255, 255, 127) : sf::Color::White);
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

}