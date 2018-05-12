#include "gui/ng/label.hpp"

#include "gui/ng/spritewidget.hpp"
#include "gui/ng/text.hpp"
#include "gui/ng/spritewidget.hpp"

namespace namelessgui
{

Label::Label()
    : _text(new Text()),
      _image(nullptr)
{
    addWidget(_text);
}

void Label::setText(const std::string& text)
{
    _text->setText(text);
}

const std::string &Label::getText() const
{
	return _text->getText();
}

void Label::setFontSize(unsigned int fontSize)
{
	_text->setCharacterSize(fontSize);
}

void Label::setImage(const sf::Texture* image)
{
    if(!_image)
    {
        _image  = new RectangularWidget();
		_image->setSize({getSize().y, getSize().y}); // Quadratic
        _image->setFillColor({255, 255, 255, 255});
        addWidget(_image);
    }

	_image->setTexture(image);
    _image->setVisible(true);
}

void Label::setSize(const sf::Vector2f &size)
{
    _size = size;
    if(_image != nullptr)
		_image->setSize({size.y, size.y}); // Quadratic
}

sf::Vector2f Label::getSize() const
{
    return _size;
}

sf::Vector2f Label::getTextSize() const
{
    return _text->getSize();
}

void Label::setPosition(const sf::Vector2f& position)
{
    _position = position;

    // Positioning with image
    if(_image)
    {
        _image->setRelativePosition({0, 0});

        _text->setAnchor({0, 1.0f});
        _text->setParentAnchor({_size.y / _size.x , 0.5});
        _text->setRelativePosition({0, 0});
    }
    // Positioning without image
    else
    {
        _text->setAnchor({0.5f, 1.0f});
        _text->setParentAnchor({0.5f, 0.5f});
        _text->setRelativePosition({0.0f, 0.0f});
    }
}

sf::Vector2f Label::getPosition() const
{
    return _position;
}

} // namespace namelessgui
