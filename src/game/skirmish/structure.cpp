#include "game/skirmish/structure.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"

#include "gui/texturemanager.hpp"
#include "gui/scene.hpp"

namespace qrw
{

SID Structure::typeName("qrw::Structure");

Structure::Structure()
	: type_(Type::WALL)
{
	spriteComponent_ = new SpriteComponent(RENDER_LAYER_STRUCTURE);
	spriteComponent_->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
	addComponent(spriteComponent_);
}

void Structure::onAddToScene()
{
	GameObject::onAddToScene();
	setPosition(getPosition());

	if(type_ == Type::WALL)
		computeTexture();
	else
		spriteComponent_->setTexture(TextureManager::getInstance()->getTexture("stairs"));
}

void Structure::initialize()
{
	GameObject::initialize();
	updateNeighborTextures();
}

void Structure::onDestroy()
{
	updateNeighborTextures();
}

void Structure::setPosition(const Coordinates& position)
{
	position_ = position;
	spriteComponent_->setPosition({SQUARE_DIMENSION * position_.getX(), SQUARE_DIMENSION * position.getY()});
}

void Structure::computeTexture()
{
	std::string textureName = "wall";

	Board* board = g_scene.findSingleGameObject<Board>();
	if(board)
	{
		if(board->getStructure(position_ + Coordinates(0, -1)))
			textureName += 'N';
		if(board->getStructure(position_ + Coordinates(1,  0)))
			textureName += 'O';
		if(board->getStructure(position_ + Coordinates(0,  1)))
			textureName += 'S';
		if(board->getStructure(position_ + Coordinates(-1, 0)))
			textureName += 'W';
	}

	spriteComponent_->setTexture(TextureManager::getInstance()->getTexture(textureName));
}

void Structure::updateNeighborTextures()
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if(auto structure = board->getStructure(position_ + Coordinates(0, -1)))
		structure->computeTexture();
	if(auto structure = board->getStructure(position_ + Coordinates(1,  0)))
		structure->computeTexture();
	if(auto structure = board->getStructure(position_ + Coordinates(0,  1)))
		structure->computeTexture();
	if(auto structure = board->getStructure(position_ + Coordinates(-1, 0)))
		structure->computeTexture();
}

} // namespace qrw
