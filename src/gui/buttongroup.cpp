#include <stdio.h>

#include "gui/buttongroup.hpp"

namespace qrw
{
	ButtonGroup::ButtonGroup()
	{}

	ButtonGroup::~ButtonGroup()
	{}

	void ButtonGroup::addButton(Button* button)
	{
		if(hasButton(button) == true)
			return;
		buttons[button] = button;
	}

	void ButtonGroup::activateButton(Button* button)
	{
		if(hasButton(button) == false)
			return;
		std::map<Button*, Button*>::iterator iter;
		for(iter = buttons.begin(); iter != buttons.end(); ++iter)
		{
			iter->second->setState(Button::ES_INACTIVE);
		}
		buttons.find(button)->second->setState(Button::ES_ACTIVE);
	}

	bool ButtonGroup::hasButton(Button* button)
	{
		return (buttons.find(button) != buttons.end());
	}
}