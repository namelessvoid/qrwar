#ifndef NAMELESSGUI_GUI_H
#define NAMELESSGUI_GUI_H

#include "gui/ng/widget.hpp"

namespace sf
{
class RenderWindow;
}

namespace namelessgui
{

class Gui : public namelessgui::Widget
{
public:
	Gui(sf::RenderWindow* renderWindow);
	virtual ~Gui();

	virtual void setSize(const sf::Vector2f& size) override;

	virtual sf::Vector2f getSize() const override;

	virtual void setPosition(const sf::Vector2f& position) override;

	virtual sf::Vector2f getPosition() const override;

private:
	sf::RenderWindow* _renderWindow;

	sf::Vector2f _size;
};

} // namespace namelessgui

#endif // NAMELESS_GUI_H
