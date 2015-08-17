#ifndef QRW_GUIHANDLER_HPP
#define QRW_GUIHANDLER_HPP

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Window.hpp>

namespace qrw
{
	class Engine;
	class BoardWidget;
	class DeployWindow;
	class IngameWindow;

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
			GuiHandler(qrw::Engine* engine, sf::RenderWindow* renderwindow);
			~GuiHandler();

			sf::RenderWindow* getRenderWindow();

			void display(sf::RenderWindow& renderwindow);

			inline bool guiVisible() { return visible; }

			/**
			 * Toggle the gui. If gui will be hidden, save the visibility stats of the windows so they can be restored
			 * when the gui is set visible again.
			 */
			void toggleGui();

			inline bool getQuit() { return quit; }
			inline void setQuit(bool quit) { this->quit = quit; }
			inline void doQuit() { this->quit = true; }

			void showStartGameWindow();
			void showSettingsWindow();

			sfg::Window::Ptr getWindowById(int id);
			DeployWindow* getDeployWindow();
			IngameWindow* getIngameWindow();

			void HandleEvent(const sf::Event& event);

		private:
			/**
			 * Hide all windows (except MainWindow) without saving the their visibility status.
			 */
			void hideAllWindows();

			qrw::Engine* engine;
			BoardWidget* boardwidget;

			sf::Clock clock;

			sf::RenderWindow* renderwindow;

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
					NoSuchWindowException() {}
					~NoSuchWindowException() {}
			};
	};
}
#endif
