#ifndef NAMELESSGUI_BUTTON_HPP
#define NAMELESSGUI_BUTTON_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/ng/spritewidget.hpp"

namespace namelessgui
{
class Button : public RectangularWidget
{
	public:
		Button(std::string id = "");
		~Button();

		void setText(std::string text);
		const std::string& getText() const;

		void setImage(const sf::Texture* texture);

		virtual void setPosition(const sf::Vector2f& position) override;
		virtual void setSize(const sf::Vector2f& size) override;

		virtual void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

	protected:
        class Label* _label;

		virtual void leftMousebuttonPressedSlot();
		virtual void mouseEnteredSlot();
		virtual void clickedSlot();
		virtual void mouseLeftSlot();
};
}

#endif
