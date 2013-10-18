#ifndef QRW_BOARDRENDERER_HPP
#define QRW_BOARDRENDERER_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include "engine/board.hpp"
#include "gui/texturemanager.hpp"
#include "gui/widget.hpp"

namespace qrw
{
	class GuiHandler;
	class DeployWindow;
	class Engine;

	class BoardWidget : public Widget
	{
		public:
			BoardWidget(GuiHandler* guihandler, Engine* engine, float width, float height);
			~BoardWidget();

			void setBoard(Board* board);

			void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		private:
			void calcSpriteDimensions(int boardwidth, int boardheight);

			void drawTerrain(sf::RenderTarget& target, TERRAINTYPES terraintype,
				sf::Vector2f position, sf::Vector2f scale) const;
			void drawUnit(sf::RenderTarget& target, int playerid, UNITTYPES unittype,
				sf::Vector2f position, sf::Vector2f scale) const;

			// Slots
			void updateCursor();
			void leftClicked();

			Engine* engine;
			Board* board;

			float spritedimensions;
			float singlespritescale;

			sf::Sprite* plainsquare;
			sf::Sprite* terrainsprites[ET_NUMBEROFTERRAINTYPES];
			sf::Sprite* p1unitsprites[EUT_NUMBEROFUNITTYPES];
			sf::Sprite* p2unitsprites[EUT_NUMBEROFUNITTYPES];

			// Pointer to deploywindow to have acces to DeployWindow::placeEntity() and DeployWindow::moveUnit().
			DeployWindow* deploywindow;
	};
}

#endif
