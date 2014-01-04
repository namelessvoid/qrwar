#include "gui/ng/spritewidget.hpp"

namespace namelessgui
{
	SpriteWidget::SpriteWidget(sf::Window* window, float width, float height)
		:	Widget(window, width, height),
			sprite()
	{
	}

	void SpriteWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if(visible)
			target.draw(sprite, states);
	}

	sf::FloatRect SpriteWidget::getGlobalBounds()
	{
		return sprite.getGlobalBounds();
	}

	void SpriteWidget::setScale(const sf::Vector2f scale)
	{
		sprite.setScale(scale);
	}

	void SpriteWidget::setScale(float scalex, float scaley)
	{
		sprite.setScale(scalex, scaley);
	}

	void SpriteWidget::setPosition(float x, float y)
	{
		sprite.setPosition(x, y);
	}

	void SpriteWidget::setPosition(const sf::Vector2f& position)
	{
		sprite.setPosition(position);
	}

	const sf::Vector2f& SpriteWidget::getPosition() const
	{
		return sprite.getPosition();
	}

	const sf::Texture* SpriteWidget::getTexture() const
	{
		return sprite.getTexture();
	}

	void SpriteWidget::setTexture(const sf::Texture& texture, bool resetRect)
	{
		sprite.setTexture(texture, resetRect);
	}

	const sf::Vector2f& SpriteWidget::getScale() const
	{
		return sprite.getScale();
	}
}