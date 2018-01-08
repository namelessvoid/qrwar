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
		button->signalClicked.connect(std::bind(&RadioToggleButton::deactivate, iter));
		iter->signalClicked.connect(std::bind(&RadioToggleButton::deactivate, button));
	}

	buttons_.insert(button);
}

} // namespace namelessgui
