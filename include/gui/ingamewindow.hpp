#ifndef QRW_INGAMEWINDOW_HPP
#define QRW_INGAMEWINDOW_HPP

#include <SFML/Graphics/Font.hpp>

#include "engine/unittypes.hpp"
#include "engine/terraintypes.hpp"

#include "gui/ng/window.hpp"

namespace namelessgui
{
class Label;
class SpriteWidget;
class Button;
} // namespace namelessgui

namespace qrw
{
	class Engine;
	class GuiHandler;

	class IngameWindow : public namelessgui::Window
	{
		public:
			IngameWindow(Engine* engine, GuiHandler* guihandler);
			~IngameWindow();

			void update();

		private:
			// private slots:
			void changeplayerbuttonClicked();

			Engine* engine;
			GuiHandler* guihandler;

			// Widgets
			namelessgui::Button* endturnbutton;
			namelessgui::Label* playernamelabel;

			// Sprites for unit information
			namelessgui::SpriteWidget* unitplainsquare;
			namelessgui::SpriteWidget* healthsprite;
			namelessgui::SpriteWidget* unitattacksprite;
			namelessgui::SpriteWidget* unitdefensesprite;
			namelessgui::SpriteWidget* movementsprite;

			// Sprites for terrain information
			namelessgui::SpriteWidget* terrainplainsquare;
			namelessgui::SpriteWidget* terrainattacksprite;
			namelessgui::SpriteWidget* terraindefensesprite;

			sf::Font* defaultfont;

			namelessgui::Label* healthtext;
			namelessgui::Label* unitattacktext;
			namelessgui::Label* unitdefensetext;
			namelessgui::Label* unitmovementtext;
			namelessgui::Label* terrainattacktext;
			namelessgui::Label* terraindefensetext;

			namelessgui::SpriteWidget* unitimages[EUT_NUMBEROFUNITTYPES * 2];
			namelessgui::SpriteWidget* terrainimages[ET_NUMBEROFTERRAINTYPES];
	};
}

#endif
