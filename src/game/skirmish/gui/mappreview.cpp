#include "game/skirmish/gui/mappreview.hpp"

#include <SFML/Graphics/Texture.hpp>

namespace qrw
{

MapPreview::MapPreview()
	: rect_(std::make_unique<sf::RectangleShape>())
{
	rect_->setFillColor(sf::Color::White);
	rect_->setRotation(45);
}

void MapPreview::setSize(const sf::Vector2f& size)
{
	size_ = size;
	updateRectangle();
}

sf::Vector2f MapPreview::getSize() const
{
	return size_;
}

sf::Vector2f MapPreview::getPosition() const
{
	return position_;
}

void MapPreview::setPosition(const sf::Vector2f& position)
{
	position_ = position;
	updateRectangle();
}

void MapPreview::setTexture(const sf::Texture& texture)
{
	rect_->setTexture(&texture);
	updateRectangle();
}

void MapPreview::render(sf::RenderTarget& target, sf::RenderStates states) const
{
	Widget::render(target, states);
	if(isVisible()) {
		target.draw(*rect_, states);
	}
}

void MapPreview::updateRectangle()
{
	const sf::Texture* texture = rect_->getTexture();
	if(!texture) return;

	rect_->setScale(1, 1);
	rect_->setSize(sf::Vector2f(texture->getSize().x, texture->getSize().y));
	rect_->setOrigin(0.5f * rect_->getSize());

	sf::Vector2f sizeMapPreview = size_;
	sf::FloatRect spriteBounds = rect_->getGlobalBounds();
	float scale = 1;

	// Only resize if texture is valid and possible preview size is > zero
	if(spriteBounds.width != 0 && spriteBounds.height != 0 && size_.x != 0 && size_.y != 0)
	{
		float scaleX = size_.x / spriteBounds.width;
		float scaleY = size_.y / spriteBounds.height;
		scale = std::min(scaleX, scaleY);
	}

	rect_->setScale(scale, scale);
	rect_->setPosition(getPosition() + 0.5f * getSize());
}

} // namespace qrw
