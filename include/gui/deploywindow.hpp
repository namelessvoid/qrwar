#ifndef QRW_DEPLOYWINDOW_HPP
#define QRW_DEPLOYWINDOW_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "engine/engine.hpp"
#include "engine/unit.hpp"
#include "gui/window.hpp"
#include "gui/button.hpp"
#include "gui/buttongroup.hpp"
#include "gui/radiotogglebutton.hpp"
#include "gui/ingamewindow.hpp"

#define BUTTONCOUNT 10

namespace qrw
{
	class GuiHandler;

	class DeployWindow : public Window
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
			RadioToggleButton* radiobuttons[BUTTONCOUNT];
			ButtonGroup* buttongroup;
			Button* startbutton;
			sf::Font* defaultfont;
			sf::Text* title;

			Engine* engine;
	};
}
#endif