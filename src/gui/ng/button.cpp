#include <stdio.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/button.hpp"

namespace namelessgui
{

	Button::Button(sf::Window* window, float width, float height, std::string text,
		const sf::Texture* textureactive,
		const sf::Texture* textureinactive,
		const sf::Texture* texturehover)
	: SpriteWidget(window, width, height),
	  text(new sf::Text()),
	  defaultfont(new sf::Font()),
	  state(ES_INACTIVE)
	{
		defaultfont->loadFromFile("./res/font/Knigqst.ttf");
		this->text->setFont(*defaultfont);
		this->text->setString("hallo");
		this->text->setCharacterSize(25);
		if(textureactive != NULL && textureinactive != NULL
			&& texturehover != NULL)
			setTextures(textureactive, textureinactive, texturehover);

		for(int i = 0; i < 3; ++i)
			textures[i] = 0;

		// Connect signals to slots
		this->signalleftmousebuttonpressed.connect(std::bind(&Button::leftMousebuttonPressedSlot, this));
		this->signalmouseentered.connect(std::bind(&Button::mouseEnteredSlot, this));
		this->signalclicked.connect(std::bind(&Button::clickedSlot, this));
		this->signalmouseleft.connect(std::bind(&Button::mouseLeftSlot, this));
	}

	Button::~Button()
	{}

	void Button::setText(std::string text)
	{
		this->text->setString(text);
	}
	std::string Button::getText()
	{
		return text->getString();
	}
	void Button::setState(Button::STATES state)
	{
		this->state = state;
	}

	Button::STATES Button::getState() const
	{
		return state;
	}

	void Button::setPosition(float x, float y)
	{
		SpriteWidget::setPosition(x, y);
		if(getTexture() != NULL)
		{
			text->setPosition(x + getTexture()->getSize().x
				* getScale().x, y);
		}
		else
		{
			text->setPosition(x, y);
		}
	}

	void Button::setPosition(const sf::Vector2f& position)
	{
		setPosition(position.x, position.y);

	}

	sf::Vector2f Button::getSize() const
	{
		sf::Vector2f size;
		size.x = text->getLocalBounds().width;
		size.y = text->getLocalBounds().height;
		if(getTexture() != NULL)
		{
			size.x += getTexture()->getSize().x * getScale().x;
			size.y = getTexture()->getSize().y * getScale().y;
		}
		return size;
	}

	void Button::setTextures(const sf::Texture* textureinactive,
		const sf::Texture* textureactive, const sf::Texture* texturehover)
	{
		textures[ES_INACTIVE] = textureinactive;
		textures[ES_ACTIVE] = textureactive;
		textures[ES_HOVER] = texturehover;
		updateSprite();
	}

	void Button::updateSprite()
	{
		if(textures[state] != 0)
		{
			setTexture(*textures[state]);
			setPosition(getPosition());
		}
	}

	void Button::leftMousebuttonPressedSlot()
	{
		state = ES_ACTIVE;
		updateSprite();
	}

	void Button::mouseEnteredSlot()
	{
		state = ES_HOVER;
		updateSprite();
	}

	void Button::clickedSlot()
	{
		state = ES_HOVER;
		updateSprite();
	}

	void Button::mouseLeftSlot()
	{
		state = ES_INACTIVE;
		updateSprite();
	}

}
