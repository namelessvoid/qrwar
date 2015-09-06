#ifndef NAMELESSGUI_BUTTON_HPP
#define NAMELESSGUI_BUTTON_HPP

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/ng/spritewidget.hpp"
#include "gui/ng/label.hpp"

namespace namelessgui
{
class Button : public RectangularWidget
{
	public:
		Button();
		~Button();

		void setText(std::string text);
		void setImage(const sf::Texture* texture);

		virtual void setPosition(const sf::Vector2f& position) override;
		virtual void setSize(const sf::Vector2f& size) override;

		virtual void render(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

	protected:
		Label* _label;
		RectangularWidget* _image;

		virtual void leftMousebuttonPressedSlot();
		virtual void mouseEnteredSlot();
		virtual void clickedSlot();
		virtual void mouseLeftSlot();
};
}

#endif
