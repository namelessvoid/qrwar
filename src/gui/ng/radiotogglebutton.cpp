#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/radiotogglebutton.hpp"

namespace namelessgui
{
	RadioToggleButton::RadioToggleButton(ButtonGroup* buttongroup,
		const sf::Texture* textureactive,
		const sf::Texture* textureinainactive,
		const sf::Texture* texturehover)
	: Button(textureactive, textureinainactive, texturehover),
	  _buttongroup(buttongroup)
	{
		buttongroup->addButton(this);
		disconnectAllSignals();
		signalclicked.connect(std::bind(&RadioToggleButton::clickedSlot, this));
	}

	RadioToggleButton::~RadioToggleButton()
	{
	}

	void RadioToggleButton::clickedSlot()
	{
		_buttongroup->activateButton(this);
		updateSprite();
	}
}
