#ifndef NAMELESSGUI_BUTTONGROUP_HPP
#define NAMELESSGUI_BUTTONGROUP_HPP

#include <map>

#include "gui/ng/radiotogglebutton.hpp"

namespace namelessgui
{
	class ButtonGroup
	{
		public:
			ButtonGroup();
			~ButtonGroup();

			void addButton(RadioToggleButton* button);

		private:
			bool hasButton(RadioToggleButton* button);

			std::map<RadioToggleButton*, RadioToggleButton*> _buttons;
	};
}

#endif
