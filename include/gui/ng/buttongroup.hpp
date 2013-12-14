#ifndef NAMELESSGUI_BUTTONGROUP_HPP
#define NAMELESSGUI_BUTTONGROUP_HPP

#include <map>

#include "gui/ng/button.hpp"

namespace namelessgui
{
	class ButtonGroup
	{
		public:
			ButtonGroup();
			~ButtonGroup();

			void addButton(Button* button);
			void activateButton(Button* button);

		private:
			bool hasButton(Button* button);

			std::map<Button*, Button*> buttons;
	};
}

#endif