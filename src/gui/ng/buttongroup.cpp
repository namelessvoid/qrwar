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
	if(_buttons.find(button) != _buttons.end())
		return;

	for(auto iter : _buttons)
	{
		button->signalclicked.connect(std::bind(&RadioToggleButton::deactivate, iter));
		iter->signalclicked.connect(std::bind(&RadioToggleButton::deactivate, button));
	}

	_buttons.insert(button);
}

} // namespace namelessgui
