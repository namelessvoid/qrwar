#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/radiotogglebutton.hpp"

namespace namelessgui
{
	RadioToggleButton::RadioToggleButton(ButtonGroup* buttongroup)
	: Button(),
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
