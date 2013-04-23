#ifndef QRW_GUIHANDLER_HPP
#define QRW_GUIHANDLER_HPP

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Window.hpp>

#include "engine/engine.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/boardrenderer.hpp"
#include "gui/placeunitwindow.hpp"

namespace qrw
{
	/**
	 * @brief Enum holding all window ids.
	 */
	enum EW_WINDOWIDS
	{
		MAINWINDOW = 0,
		STARTGAMEWINDOW,
		LOADGANEWINDO,
		SETTINGSWINDOW,
		CREDITSWINDOW,
		// This one is just used to now the
		// number of windos.
		NUMEROFWINDOWS
	};

	/**
	 * @brief Main class handling the gui.
	 */
	class GuiHandler : public sfg::Desktop
	{
		public:
			GuiHandler(qrw::Engine* engine, sf::Vector2f windowsize);
			~GuiHandler();

			void display(sf::RenderTarget& rendertarget);

			inline bool guiVisible() { return visible; };

			void toggleGui();

			inline bool getQuit() { return quit; };
			inline void setQuit(bool quit) { this->quit = quit; };
			inline void doQuit() { this->quit = true; };

			void showStartGameWindow();

			sfg::Window::Ptr getWindowById(int id);

			void HandleEvent(const sf::Event& event);

		private:
			qrw::Engine* engine;
			BoardRenderer boardrenderer;

			sf::Vector2f windowsize;
			
			sfg::Window::Ptr windows[NUMEROFWINDOWS];
			bool visiblestats[NUMEROFWINDOWS];
			IngameWindow::Ptr ingamewindow;
			PlaceUnitWindow::Ptr placeunitwindow;

			sfg::SFGUI sfgui;
			bool visible;
			bool quit;

			class NoSuchWindowException
			{
				public:
					NoSuchWindowException() {};
					~NoSuchWindowException() {};
			};
	};
}
#endif