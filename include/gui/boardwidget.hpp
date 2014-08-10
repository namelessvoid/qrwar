#ifndef QRW_BOARDRENDERER_HPP
#define QRW_BOARDRENDERER_HPP

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

#include "engine/terrain.hpp"
#include "engine/unit.hpp"

#include "gui/ng/widget.hpp"

namespace qrw
{
	class GuiHandler;
	class DeployWindow;
	class Board;
	class Engine;
	class Path;

	class BoardWidget : public namelessgui::Widget
	{
		public:
			BoardWidget(GuiHandler* guihandler, Engine* engine, float width, float height);
			~BoardWidget();

			void setBoard(Board* board);

			void draw(sf::RenderTarget &target, sf::RenderStates states) const;

			sf::FloatRect getGlobalBounds()
			{
				return sf::FloatRect(0, 0, getSize().x, getSize().y);
			}

		private:
			void calcSpriteDimensions(int boardwidth, int boardheight);

			void drawTerrain(sf::RenderTarget& target, TERRAINTYPES terraintype,
				sf::Vector2f position, sf::Vector2f scale) const;
			void drawUnit(sf::RenderTarget& target, int playerid, UNITTYPES unittype,
				sf::Vector2f position, sf::Vector2f scale) const;
			void drawPath(sf::RenderTarget& target, sf::Vector2f scale) const;

			void moveUnitIngame();

			// Slots
			void updateCursor();
			void leftClicked();
			void rightClicked();
			void keyPressed(const sf::Event& event);

			Engine* engine;
			Board* board;

			float spritedimensions;
			float singlespritescale;

			sf::Sprite* plainsquare;
			sf::Sprite* footstep;
			sf::Sprite* terrainsprites[ET_NUMBEROFTERRAINTYPES];
			sf::Sprite* p1unitsprites[EUT_NUMBEROFUNITTYPES];
			sf::Sprite* p2unitsprites[EUT_NUMBEROFUNITTYPES];

			Path* path;

			// Pointer to deploywindow to have acces to DeployWindow::placeEntity() and DeployWindow::moveUnit().
			DeployWindow* deploywindow;
	};
}

#endif
