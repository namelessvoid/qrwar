#ifndef NAMELESSGUI_SPRITEWIDGET_HPP
#define NAMELESSGUI_SPRITEWIDGET_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/ng/widget.hpp"

namespace namelessgui
{
class SpriteWidget : public Widget, public sf::RectangleShape
{
public:
	SpriteWidget(sf::RenderWindow* window, float width, float height);

	sf::Vector2f getSize() const;

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
