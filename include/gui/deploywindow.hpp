#ifndef QRW_DEPLOYWINDOW_HPP
#define QRW_DEPLOYWINDOW_HPP

#include <SFML/Graphics/RenderTarget.hpp>

#include "engine/engine.hpp"
#include "engine/unit.hpp"
#include "gui/button.hpp"

namespace qrw
{
	class GuiHandler;

	class DeployWindow : public sf::Drawable
	{
		public:
			DeployWindow(Engine* engine, GuiHandler* guihandler);
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

			Button* startbutton;

			Engine* engine;
			// Arrays of player units
			int p1units[EUT_NUMBEROFUNITTYPES];
			int p2units[EUT_NUMBEROFUNITTYPES];			
	};
}
#endif