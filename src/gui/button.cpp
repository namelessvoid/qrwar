#include <stdio.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/button.hpp"

namespace qrw
{

	Button::Button(sf::Window* window,std::string text,
		const sf::Texture* textureactive,
		const sf::Texture* textureinactive,
		const sf::Texture* texturehover)
	: Sprite(),
	  text(text),
	  window(window),
	  state(ES_INACTIVE)
	{
		if(textureactive != NULL && textureinactive != NULL
			&& texturehover != NULL)
			setTextures(textureactive, textureinactive, texturehover);

		for(int i = 0; i < 3; ++i)
			textures[i] = 0;
	}

	Button::~Button()
	{}

	void Button::setText(std::string text)
	{
		this->text = text;
	}
	std::string Button::getText()
	{
		return text;
	}
	void Button::setState(Button::STATES state)
	{
		this->state = state;
	}

	Button::STATES Button::getState()
	{
		return state;
	}
	
	void Button::setTextures(const sf::Texture* textureinactive,
		const sf::Texture* textureactive, const sf::Texture* texturehover)
	{
		textures[ES_INACTIVE] = textureinactive;
		textures[ES_ACTIVE] = textureactive;
		textures[ES_HOVER] = texturehover;
	}

	void Button::handleEvent(const sf::Event& event)
	{
		if(mouseOnButton() == false)
		{
			state = ES_INACTIVE;
			updateSprite();
			return;
		}
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) == false
			&& event.type == sf::Event::MouseMoved)
		{
			state = ES_HOVER;
		}
		else if(event.type == sf::Event::MouseButtonPressed
			&& event.mouseButton.button == sf::Mouse::Left)
		{
			state = ES_ACTIVE;
			signalclicked.emit();
		}
		else if(event.type == sf::Event::MouseButtonReleased
			&& event.mouseButton.button == sf::Mouse::Left)
		{
			state = ES_INACTIVE;
		}
		updateSprite();
	}

	bool Button::mouseOnButton()
	{
		sf::FloatRect bounds = getGlobalBounds();
		sf::Vector2f mousepos;
		mousepos.x = (float)sf::Mouse::getPosition(*window).x;
		mousepos.y = (float)sf::Mouse::getPosition(*window).y;
		return getGlobalBounds().contains(mousepos);
	}

	void Button::updateSprite()
	{
		if(textures[state] != 0)
			setTexture(*textures[state]);
	}
}