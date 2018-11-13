#include "game/skirmish/boardbackgroundcomponent.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <game/constants.hpp>

#include "game/renderlayers.hpp"

#include "gui/texturemanager.hpp"

namespace qrw
{

BoardBackgroundComponent::BoardBackgroundComponent(Board& owner)
	: Renderable(RENDER_LAYER_BACKGROUND),
	  owner_(owner)
{
	plainSquareSprite_.setTexture(*TextureManager::getInstance()->getTexture("plainsquare"));
}

void BoardBackgroundComponent::render(sf::RenderTarget& renderTarget)
{
	for(unsigned int x = 0; x < owner_.getWidth(); ++x)
	{
		for(unsigned int y = 0; y < owner_.getHeight(); ++y)
		{
			float twoDimX = x * SQUARE_DIMENSION;
			float twoDimY = y * SQUARE_DIMENSION;

			float isoX = twoDimX - twoDimY;
			float isoY = (twoDimX + twoDimY) / 2.0f;
			plainSquareSprite_.setPosition({isoX, isoY});
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


} // namespace qrw
