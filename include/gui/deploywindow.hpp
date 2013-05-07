#ifndef QRW_DEPLOYWINDOW_HPP
#define QRW_DEPLOYWINDOW_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "engine/engine.hpp"
#include "engine/unit.hpp"
#include "gui/button.hpp"
#include "gui/buttongroup.hpp"
#include "gui/radiotogglebutton.hpp"
#include "gui/ingamewindow.hpp"

#define BUTTONCOUNT 9

namespace qrw
{
	class GuiHandler;

	class DeployWindow : public sf::Drawable
	{
		public:
			DeployWindow(Engine* engine, GuiHandler* guihandler,
				IngameWindow* ingamewindow);
			~DeployWindow();

			void setVisible(bool visible);
			void draw(sf::RenderTarget&,
				sf::RenderStates = sf::RenderStates::Default) const;

			void update();
			void setPlayerUnits(int playerunits[]);

			void handleEvent(const sf::Event& event);

		private:
			// Private slots
			void startbuttonClicked();
			void placeEntity();
			
			bool visible;

			IngameWindow* ingamewindow;
			// Buttons for units and terrain
			RadioToggleButton* radiobuttons[BUTTONCOUNT];
			ButtonGroup* buttongroup;
			Button* startbutton;
			sf::Font* defaultfont;
			sf::Text* title;

			Engine* engine;
			// Arrays of player units
			int playerunits[2*EUT_NUMBEROFUNITTYPES];
	};
}
#endif