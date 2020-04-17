#include "game/deploymentzone.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/texturemanager.hpp"
#include "gui/scene.hpp"
#include "game/renderlayers.hpp"
#include "game/constants.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/stairs.hpp"
#include "game/skirmish/isometricconversion.hpp"
#include "game/skirmish/boardtoworldconversion.hpp"

namespace qrw
{

const SID DeploymentZone::typeName("qrw::DeploymentZone");

DeploymentZone::DeploymentZone()
    : GameObject(),
      playerId_(-1),
      color_(sf::Color::Green)
{
}

void DeploymentZone::initialize()
{
	GameObject::initialize();
	updateSprites();
}

void DeploymentZone::addSquare(const Coordinates& coordinates)
{
	assert(zone_.find(coordinates) == zone_.end());

    zone_.insert(coordinates);

    auto* sprite = new SpriteComponent(RENDER_LAYER_GAME);
    sprite->setFillColor(color_);
	addComponent(sprite);
	sprites_[coordinates] = sprite;

	// Only update sprite when we are sure that the scene has a Board instance.
	if(isInitialized()) {
		updateSprite(coordinates, sprite);
	}
}

void DeploymentZone::removeSquare(const Coordinates& coordinates)
{
	assert(zone_.find(coordinates) != zone_.end());

    zone_.erase(coordinates);

    auto* sprite = sprites_[coordinates];
    removeComponent(sprite);
    sprites_.erase(coordinates);
    delete sprite;
}

bool DeploymentZone::containsSquare(const Coordinates& coordinate)
{
    return zone_.find(coordinate) != zone_.end();
}

void qrw::DeploymentZone::crop(const Coordinates& size)
{
	auto iter = zone_.begin();
	while(iter != zone_.end())
	{
		Coordinates square = *iter;
		if(square.getX() >= size.getX() || square.getY() >= size.getY())
			iter = zone_.erase(iter);
		else
			++iter;
	}
}

void DeploymentZone::setPlayerId(int playerId)
{
    playerId_ = playerId;

    switch(playerId)
    {
        case 1: color_ = PLAYER_ONE_COLOR; break;
        case 2: color_ = PLAYER_TWO_COLOR; break;
        default: assert(playerId == 1 || playerId == 2);
    }
}

void DeploymentZone::flatModeChanged()
{
	updateSprites();
}

void DeploymentZone::updateSprites()
{
	for(const auto& iter : sprites_) {
		updateSprite(iter.first, iter.second);
	}
}

void DeploymentZone::updateSprite(const Coordinates& coordinates, SpriteComponent* sprite)
{
	auto* board = g_scene.findSingleGameObject<Board>();
	assert(board != nullptr);

	sprite->setPosition(worldToIso(boardToWorld(coordinates)));
	float zIndex = sprite->getZIndex() + 0.02f;

	std::string textureName = "deploymentzone";
	sf::Vector2f spriteOrigin(SQUARE_DIMENSION, 0.0f);
	sf::Vector2f spriteSize(2.0f * SQUARE_DIMENSION, SQUARE_DIMENSION);
	float heightOffset = 0;

	if(!isFlatMode()) {
		if (auto* structure = board->getStructure(coordinates)) {
			if (dynamic_cast<Wall*>(structure) != nullptr) {
				heightOffset = -2.0f * SQUARE_DIMENSION;
			} else if (auto stairs = dynamic_cast<Stairs*>(structure)) {
				textureName += "_stairs_";
				if (stairs->getFace() == Directions::WEST) {
					textureName += "west";
				} else if (stairs->getFace() == Directions::NORTH) {
					textureName += "north";
				} else if (stairs->getFace() == Directions::EAST) {
					textureName += "east";
				} else if (stairs->getFace() == Directions::SOUTH) {
					textureName += "south";
				}

				spriteOrigin = sf::Vector2f(SQUARE_DIMENSION, 40.0f);
				spriteSize = sf::Vector2f(2.0f * SQUARE_DIMENSION, 91.0f);
			}
		}
	}

	sprite->setTexture(TextureManager::getInstance()->getTexture(textureName));
	sprite->setSize(spriteSize);
	sprite->setOrigin(spriteOrigin.x, spriteOrigin.y);
	sprite->setPosition(sprite->getPosition() + sf::Vector2f(0, heightOffset));
	sprite->setZIndex(zIndex);
}

} // namespace qrw
