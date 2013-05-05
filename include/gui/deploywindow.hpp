#ifndef QRW_DEPLOYWINDOW_HPP
#define QRW_DEPLOYWINDOW_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "engine/engine.hpp"
#include "engine/unit.hpp"
#include "gui/button.hpp"
#include "gui/ingamewindow.hpp"

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
			void setPlayerUnits(int p1units[], int p2units[]);

			void handleEvent(const sf::Event& event);

		private:
			// Private slots
			void startbuttonClicked();
			
			bool visible;

			IngameWindow* ingamewindow;
			Button* startbutton;
			sf::Font* defaultfont;
			sf::Text* title;

			Engine* engine;
			// Arrays of player units
			int p1units[EUT_NUMBEROFUNITTYPES];
			int p2units[EUT_NUMBEROFUNITTYPES];			
	};
}
#endif