#ifndef NAMELESSGUI_SPRITEWIDGET_HPP
#define NAMELESSGUI_SPRITEWIDGET_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/ng/widget.hpp"

namespace namelessgui
{

/**
 * @brief A rectangular widget that can be filled with color and be surrounded
 * by a colored border.
 */
class RectangularWidget : public Widget, public sf::RectangleShape
{
public:
	RectangularWidget(std::string id = "");

	sf::Vector2f getSize() const;

	void setScale(const sf::Vector2f &factors);

	void setScale(float scaleX, float scaleY);

	sf::Vector2f getPosition() const;

	void setPosition(const sf::Vector2f& position) override;

	virtual void render(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void setSize(const sf::Vector2f& size) override;

	virtual sf::FloatRect getWidgetArea() const;

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

} // namespace namelessgui

#endif // NAMELESSGUI_SPRITEWIDGET_HPP
