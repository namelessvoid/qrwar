#ifndef NAMELESSGUI_BUTTONGROUP_HPP
#define NAMELESSGUI_BUTTONGROUP_HPP

#include <set>

#include "gui/ng/radiotogglebutton.hpp"

namespace namelessgui
{

class ButtonGroup
{
public:
	ButtonGroup() {}
	~ButtonGroup() {}

	void addButton(RadioToggleButton* button);

private:
	std::set<RadioToggleButton*> buttons_;
};

} // namespace namelessgui

#endif // NAMELESSGUI_BUTTONGROUP_HPP
