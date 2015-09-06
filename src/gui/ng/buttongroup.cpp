#include <stdio.h>

#include "gui/ng/buttongroup.hpp"

namespace namelessgui
{
ButtonGroup::ButtonGroup()
{}

ButtonGroup::~ButtonGroup()
{}

void ButtonGroup::addButton(RadioToggleButton* button)
{
	if(hasButton(button) == true)
		return;

	for(auto iter : _buttons)
	{
		button->signalclicked.connect(std::bind(&RadioToggleButton::deactivate, iter.second));
		iter.second->signalclicked.connect(std::bind(&RadioToggleButton::deactivate, button));
	}
	_buttons[button] = button;
}

bool ButtonGroup::hasButton(RadioToggleButton* button)
{
	return (_buttons.find(button) != _buttons.end());
}

} // namespace namelessgui
