#ifndef QRW_GUIHANDLER_HPP
#define QRW_GUIHANDLER_HPP

#include <SFML/System/Clock.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Window.hpp>

#include "engine/engine.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/boardwidget.hpp"
#include "gui/deploywindow.hpp"

namespace qrw
{
	/**
	 * @brief Enum holding all window ids.
	 */
	enum EW_WINDOWIDS
	{
		MAINWINDOW = 0,
		STARTGAMEWINDOW,
		LOADGAMEWINDOW,
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
			GuiHandler(qrw::Engine* engine, sf::Window* renderwindow);
			~GuiHandler();

			sf::Window* getRenderWindow();

			void display(sf::RenderTarget& rendertarget);

			inline bool guiVisible() { return visible; };

			void toggleGui();

			inline bool getQuit() { return quit; };
			inline void setQuit(bool quit) { this->quit = quit; };
			inline void doQuit() { this->quit = true; };

			void showStartGameWindow();

			sfg::Window::Ptr getWindowById(int id);
			DeployWindow* getDeployWindow();
			IngameWindow* getIngameWindow();

			void HandleEvent(const sf::Event& event);

		private:
			qrw::Engine* engine;
			BoardWidget* boardwidget;

			sf::Clock clock;

			sf::Window* renderwindow;

			sfg::Window::Ptr windows[NUMEROFWINDOWS];
			bool visiblestats[NUMEROFWINDOWS];
			DeployWindow* deploywindow;
			IngameWindow* ingamewindow;

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