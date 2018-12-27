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

}