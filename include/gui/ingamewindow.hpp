#ifndef QRW_INGAMEWINDOW_HPP
#define QRW_INGAMEWINDOW_HPP

#include <SFML/Graphics/Font.hpp>

#include "engine/unittypes.hpp"
#include "engine/terraintypes.hpp"

#include "gui/ng/window.hpp"

namespace namelessgui
{
class Label;
class RectangularWidget;
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

			Engine* _engine;
			GuiHandler* _guihandler;

			// Widgets
			namelessgui::Button* _endturnbutton;
			namelessgui::Label* _playernamelabel;

			// Sprites for unit information
			namelessgui::RectangularWidget* _unitplainsquare;
			namelessgui::RectangularWidget* _healthsprite;
			namelessgui::RectangularWidget* _unitattacksprite;
			namelessgui::RectangularWidget* _unitdefensesprite;
			namelessgui::RectangularWidget* _movementsprite;

			// Sprites for terrain information
			namelessgui::RectangularWidget* _terrainplainsquare;
			namelessgui::RectangularWidget* _terrainattacksprite;
			namelessgui::RectangularWidget* _terraindefensesprite;

			sf::Font* _defaultfont;

			namelessgui::Label* _healthtext;
			namelessgui::Label* _unitattacktext;
			namelessgui::Label* _unitdefensetext;
			namelessgui::Label* _unitmovementtext;
			namelessgui::Label* _terrainattacktext;
			namelessgui::Label* _terraindefensetext;

			namelessgui::RectangularWidget* _unitimages[EUT_NUMBEROFUNITTYPES * 2];
			namelessgui::RectangularWidget* _terrainimages[ET_NUMBEROFTERRAINTYPES];
	};
}

#endif
