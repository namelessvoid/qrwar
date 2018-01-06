#include <stdio.h>

#include "gui/ng/buttongroup.hpp"

namespace namelessgui
{

void ButtonGroup::addButton(RadioToggleButton* button)
{
	if(buttons_.find(button) != buttons_.end())
		return;

	for(auto iter : buttons_)
	{
		button->signalclicked.connect(std::bind(&RadioToggleButton::deactivate, iter));
		iter->signalclicked.connect(std::bind(&RadioToggleButton::deactivate, button));
	}

	buttons_.insert(button);
}

} // namespace namelessgui
