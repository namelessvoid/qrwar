#include "gui/ng/label.hpp"

#include "gui/ng/spritewidget.hpp"
#include "gui/ng/text.hpp"
#include "gui/ng/spritewidget.hpp"

namespace namelessgui
{

Label::Label()
    : _text(new Text()),
      _image(nullptr),
      wordWrap_(false)
{
    addWidget(_text);
}

void Label::setText(const std::string& text)
{
    if(wordWrap_)
        _text->setText(applyWordWrap(text));
    else
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

std::string Label::applyWordWrap(const std::string& original)
{
    const sf::Font* font = _text->getFont();

    std::string wrapped = original;
    float currentLineLength = 0;
    size_t lastSpacePos = wrapped.find(' ');

    for(size_t currentIndex = lastSpacePos; currentIndex < wrapped.size(); ++currentIndex)
    {
        char currentCharacter = wrapped[currentIndex];
        if(currentCharacter == ' ')
            lastSpacePos = currentIndex;
        else if(currentCharacter == '\n')
        {
            lastSpacePos = currentIndex;
            currentLineLength = 0;
        }

        const sf::Glyph& glyph = font->getGlyph(currentCharacter, _text->getCharacterSize(), false);
        currentLineLength += glyph.advance;

        if(currentLineLength > getSize().x && lastSpacePos != std::string::npos)
        {
            wrapped.replace(lastSpacePos, 1, "\n");
            currentLineLength = 0;
            currentIndex = lastSpacePos;
            lastSpacePos = std::string::npos;
        }
    }

    return wrapped;
}

} // namespace namelessgui
