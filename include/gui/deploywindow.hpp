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
	class Text;
} // namespace namelessgui

namespace qrw
{

	class Engine;
	class GuiHandler;
	class IngameWindow;

	class DeployWindow : public namelessgui::Window
	{
		public:
			DeployWindow(sf::RenderWindow* renderWindow, Engine* engine, GuiHandler* guihandler,
				IngameWindow* ingamewindow);
			~DeployWindow();

			void update();

			void placeEntity();
			void moveUnit();

		private:
			// Private slots
			void startbuttonClicked();

			Engine* _engine;

			IngameWindow* _ingamewindow;
			// Buttons for units and terrain
			namelessgui::RadioToggleButton* _radiobuttons[BUTTONCOUNT];
			namelessgui::ButtonGroup* _buttongroup;
			namelessgui::Button* _startbutton;
			sf::Font* _defaultfont;
			namelessgui::Text* _title;
	};
}
#endif
