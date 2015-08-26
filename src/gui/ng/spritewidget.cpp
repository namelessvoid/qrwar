#include "gui/ng/spritewidget.hpp"

namespace namelessgui
{

RectangularWidget::RectangularWidget(sf::RenderWindow* window, float width, float height)
	: Widget(window, width, height),
	  sf::RectangleShape(sf::Vector2f(width, height))
{
	setFillColor(sf::Color(255, 255, 0, 0));
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

void RectangularWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(_visible)
		target.draw(static_cast<sf::RectangleShape>(*this), states);
	Widget::draw(target, states);
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
