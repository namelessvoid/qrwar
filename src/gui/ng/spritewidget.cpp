#include "gui/ng/spritewidget.hpp"

namespace namelessgui
{

RectangularWidget::RectangularWidget()
	: Widget(),
	  sf::RectangleShape(sf::Vector2f())
{
	setFillColor(sf::Color(255, 255, 0, 0));

	// Reset texture pointers
	for(int i = 0; i < EWidgetStates::EWS_COUNT; ++i)
		_textures[i] = nullptr;
}

sf::Vector2f RectangularWidget::getSize() const
{
	return sf::RectangleShape::getSize();
}

void RectangularWidget::setScale(const sf::Vector2f& factors)
{
	sf::RectangleShape::setScale(factors);
}

void RectangularWidget::setScale(float scaleX, float scaleY)
{
	sf::RectangleShape::setScale(scaleX, scaleY);
}

sf::Vector2f RectangularWidget::getPosition() const
{
	return sf::RectangleShape::getPosition();
}

void RectangularWidget::setPosition(const sf::Vector2f& position)
{
	sf::RectangleShape::setPosition(position);
}

void RectangularWidget::render(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(_visible)
		target.draw(static_cast<sf::RectangleShape>(*this), states);
	Widget::render(target, states);
}

sf::FloatRect RectangularWidget::getGlobalBounds()
{
	return sf::RectangleShape::getGlobalBounds();
}

void RectangularWidget::setTexture(const sf::Texture* texture, bool resetRect)
{
	sf::RectangleShape::setTexture(texture, resetRect);
}

} // namespace namelessgui
