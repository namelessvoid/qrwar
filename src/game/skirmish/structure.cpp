#include "game/skirmish/structure.hpp"

#include "foundation/spritecomponent.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"
#include "game/skirmish/isometricconversion.hpp"

#include "gui/texturemanager.hpp"
#include "gui/scene.hpp"

namespace qrw
{

Structure::Structure()
{
	spriteComponent_ = new SpriteComponent(RENDER_LAYER_STRUCTURE);
	spriteComponent_->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
	spriteComponent_->setOrigin(SQUARE_DIMENSION * 0.5f, 0);
	addComponent(spriteComponent_);
}

void Structure::onAddToScene()
{
	GameObject::onAddToScene();
	setPosition(getPosition());
	computeTexture();
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
	spriteComponent_->setPosition(worldToIso({SQUARE_DIMENSION * position_.getX(), SQUARE_DIMENSION * position.getY()}));
}

const sf::Texture* qrw::Structure::getTexture() const
{
	return spriteComponent_->getTexture();
}

void Structure::updateNeighborTextures()
{
	Board* board = g_scene.findSingleGameObject<Board>();
	if(!board) return;

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
