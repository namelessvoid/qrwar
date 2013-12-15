#ifndef QRW_DEPLOYWINDOW_HPP
#define QRW_DEPLOYWINDOW_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "engine/engine.hpp"
#include "engine/unit.hpp"
#include "gui/ng/window.hpp"
#include "gui/ng/button.hpp"
#include "gui/ng/buttongroup.hpp"
#include "gui/ng/radiotogglebutton.hpp"
#include "gui/ingamewindow.hpp"

#define BUTTONCOUNT 10

namespace qrw
{
	class GuiHandler;

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