#ifndef NAMELESSGUI_TABWIDGET_HPP
#define NAMELESSGUI_TABWIDGET_HPP

#include <memory>

#include "widget.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace namelessgui {

class ButtonGroup;
class RadioToggleButton;

class TabWidget : public Widget
{
public:
    TabWidget();

    ~TabWidget();

	void addTab(const sf::Texture* buttonImage, Widget* widget);

    void setButtonSize(const sf::Vector2f& buttonSize);

    void setActiveTab(size_t index);

    // Widget interface
    virtual sf::FloatRect getGlobalBounds() override;
    virtual void setSize(const sf::Vector2f& size) override;
    virtual sf::Vector2f getSize() const override;
    virtual sf::Vector2f getPosition() const override;
    virtual void setPosition(const sf::Vector2f& position) override;

private:
    TabWidget(const TabWidget& rhs) = delete;

    TabWidget& operator=(const TabWidget& rhs) = delete;

    sf::Vector2f getButtonRelativePosition(int index);

    sf::Vector2f size_;
    sf::Vector2f position_;

    sf::Vector2f buttonSize_;

    std::shared_ptr<ButtonGroup> buttonGroup_;
    std::vector<RadioToggleButton*> buttons_;
    std::vector<Widget*> widgets_;
};

} // namespace namelessgui

#endif // NAMELESSGUI_TABWIDGET_HPP
