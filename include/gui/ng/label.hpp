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
    inline void setWordWrap(bool wordWrap) { wordWrap_ = wordWrap; }

    void setImage(const sf::Texture* image);

    virtual void setSize(const sf::Vector2f& size) override;
    virtual sf::Vector2f getSize() const override;
    sf::Vector2f getTextSize() const;

    virtual void setPosition(const sf::Vector2f& position) override;
    virtual sf::Vector2f getPosition() const override;

private:
    std::string applyWordWrap(const std::string& original);

    class Text* _text;
    class RectangularWidget* _image;

    sf::Vector2f _position;
    sf::Vector2f _size;

    bool wordWrap_;
};

} // namespace namelessgui

#endif // NAMELESSGUI_LABEL_HPP
