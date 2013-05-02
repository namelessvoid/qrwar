#ifndef QRW_INGAMEWINDOW_HPP
#define QRW_INGAMEWINDOW_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/engine.hpp"
#include "gui/button.hpp"

namespace qrw
{
	class GuiHandler;
	
	class IngameWindow : public sf::Drawable
	{
		public:
			IngameWindow(Engine* engine, GuiHandler* guihandler);
			~IngameWindow();

			sf::Vector2f getSize();

			void update();

			void handleEvent(const sf::Event& event);
			void draw(sf::RenderTarget&,
				sf::RenderStates = sf::RenderStates::Default) const;

		private:
			// private slots:
			void changeplayerbuttonClicked();

			Engine* engine;
			GuiHandler* guihandler;

			// Widgets
			Button endturnbutton;
			sf::Text playernamelabel;
			sf::Sprite* unitsprite;
			sf::Sprite* terrainsprite;
			sf::Sprite* plainsquare;
			sf::Font* defaultfont;

			sf::RectangleShape* background;
			sf::RectangleShape* border;
	};
}

#endif