#include "game/skirmish/boardbackgroundcomponent.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "game/constants.hpp"
#include "game/skirmish/isometricconversion.hpp"

#include "game/renderlayers.hpp"

#include "gui/texturemanager.hpp"

namespace qrw
{

BoardBackgroundComponent::BoardBackgroundComponent(Board& owner)
	: Renderable(RENDER_LAYER_BACKGROUND),
	  owner_(owner)
{
	plainSquareSprite_.setTexture(*TextureManager::getInstance()->getTexture("plainsquare"));
	plainSquareSprite_.setOrigin({SQUARE_DIMENSION, 0});
}

void BoardBackgroundComponent::render(sf::RenderTarget& renderTarget)
{
	for(unsigned int x = 0; x < owner_.getWidth(); ++x)
	{
		for(unsigned int y = 0; y < owner_.getHeight(); ++y)
		{
			sf::Vector2f isoPosition = worldToIso(sf::Vector2f(x, y) * SQUARE_DIMENSION);
			plainSquareSprite_.setPosition(isoPosition);
			renderTarget.draw(plainSquareSprite_);
		}
	}
}

void BoardBackgroundComponent::setPosition(const sf::Vector2f& position)
{
	throw "Not implemented";
}

const sf::Vector2f& BoardBackgroundComponent::getPosition() const
{
	throw "Not implemented";
}

sf::Vector2f BoardBackgroundComponent::getCenter() const
{
	return worldToIso(sf::Vector2f(owner_.getWidth(), owner_.getHeight()) * 0.5f * SQUARE_DIMENSION);
}


} // namespace qrw
