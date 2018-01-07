#ifndef NAMELESSGUI_LABEL_HPP
#define NAMELESSGUI_LABEL_HPP

#include "gui/ng/widget.hpp"

namespace namelessgui
{

class Label : public Widget
{
public:
    Label();

    void setText(const std::string& text);
    const std::string& getText() const;

	void setFontSize(unsigned int fontSize);

    void setImage(const sf::Texture* image);

    virtual sf::FloatRect getGlobalBounds() override;

    virtual void setSize(const sf::Vector2f& size) override;
    virtual sf::Vector2f getSize() const override;

    virtual void setPosition(const sf::Vector2f& position) override;
    virtual sf::Vector2f getPosition() const override;

private:
    class Text* _text;
    class RectangularWidget* _image;

    sf::Vector2f _position;
    sf::Vector2f _size;
};

} // namespace namelessgui

#endif // NAMELESSGUI_LABEL_HPP
