#ifndef QRW_DEPLOYWINDOW_HPP
#define QRW_DEPLOYWINDOW_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "gui/ng/window.hpp"

#define BUTTONCOUNT 10

namespace namelessgui
{
	class Button;
	class ButtonGroup;
	class RadioToggleButton;
	class Label;
} // namespace namelessgui

namespace qrw
{

	class Engine;
	class GuiHandler;
	class IngameWindow;

	class DeployWindow : public namelessgui::Window
	{
		public:
			DeployWindow(Engine* engine, GuiHandler* guihandler,
				IngameWindow* ingamewindow);
			~DeployWindow();

			void update();

			void placeEntity();
			void moveUnit();

		private:
			// Private slots
			void startbuttonClicked();

			IngameWindow* ingamewindow;
			// Buttons for units and terrain
			namelessgui::RadioToggleButton* radiobuttons[BUTTONCOUNT];
			namelessgui::ButtonGroup* buttongroup;
			namelessgui::Button* startbutton;
			sf::Font* defaultfont;
			namelessgui::Label* title;

			Engine* engine;
	};
}
#endif
