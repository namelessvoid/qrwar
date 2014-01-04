#ifndef QRW_INGAMEWINDOW_HPP
#define QRW_INGAMEWINDOW_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/engine.hpp"
#include "engine/unit.hpp"
#include "engine/terrain.hpp"
#include "gui/ng/window.hpp"
#include "gui/ng/button.hpp"
#include "gui/ng/label.hpp"

namespace qrw
{
	class GuiHandler;

	class IngameWindow : public namelessgui::Window
	{
		public:
			IngameWindow(Engine* engine, GuiHandler* guihandler);
			~IngameWindow();

			sf::Vector2f getSize();

			void update();

			void draw(sf::RenderTarget&,
				sf::RenderStates = sf::RenderStates::Default) const;


		private:
			// private slots:
			void changeplayerbuttonClicked();

			Engine* engine;
			GuiHandler* guihandler;

			// Widgets
			namelessgui::Button endturnbutton;
			namelessgui::Label playernamelabel;

			sf::Sprite* plainsquare;

			sf::Sprite* healthsprite;
			sf::Sprite* attacksprite;
			sf::Sprite* defensesprite;
			sf::Sprite* movementsprite;

			sf::Font* defaultfont;

			namelessgui::Label* healthtext;
			namelessgui::Label* unitattacktext;
			namelessgui::Label* unitdefensetext;
			namelessgui::Label* unitmovementtext;
			namelessgui::Label* terrainattacktext;
			namelessgui::Label* terraindefensetext;

			namelessgui::SpriteWidget* unitimages[EUT_NUMBEROFUNITTYPES * 2];
			namelessgui::SpriteWidget* terrainimages[ET_NUMBEROFTERRAINTYPES];

			sf::RectangleShape* background;
			sf::RectangleShape* border;
	};
}

#endif