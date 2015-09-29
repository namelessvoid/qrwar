#include "gui/ng/spritewidget.hpp"

namespace namelessgui
{

RectangularWidget::RectangularWidget(std::string id)
	: Widget(id),
	  sf::RectangleShape(sf::Vector2f())
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

void RectangularWidget::setSize(const sf::Vector2f& size)
{
	sf::RectangleShape::setSize(size);
	setTextureRect({0, 0, (int)size.x, (int)size.y});
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
