#ifndef NAMELESSGUI_SPRITEWIDGET_HPP
#define NAMELESSGUI_SPRITEWIDGET_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/ng/widget.hpp"

namespace namelessgui
{
class RectangularWidget : public Widget, public sf::RectangleShape
{
public:
	RectangularWidget(sf::RenderWindow* _window, float width = 10, float height = 10);

	sf::Vector2f getSize() const;

	void setScale(const sf::Vector2f &factors);

	void setScale(float scaleX, float scaleY);

	sf::Vector2f getPosition() const { return sf::RectangleShape::getPosition(); }
	void setPosition(float x, float y) { sf::RectangleShape::setPosition(x, y); }
	void setPosition(sf::Vector2f position) { sf::RectangleShape::setPosition(position); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/**
	 * Returns the global boundaries of the widget.
	 *
	 * @return The global boundary rectangle.
	 */
	sf::FloatRect getGlobalBounds() override;

	/**
	 * Sets the texture of the widget.
	 *
	 * Overwrites sf::RectangleShape::setTexture to set resetRecht to to true by default.
	 *
	 * @param texture
	 * @param resetRect
	 */
	void setTexture(const sf::Texture* texture, bool resetRect = true);
};
}
#endif
