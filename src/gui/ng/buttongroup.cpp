#include <stdio.h>

#include "gui/ng/buttongroup.hpp"

namespace namelessgui
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
			iter->second->setState(Button::EWS_INACTIVE);
		}
		buttons.find(button)->second->setState(Button::EWS_ACTIVE);
	}

	bool ButtonGroup::hasButton(Button* button)
	{
		return (buttons.find(button) != buttons.end());
	}
}