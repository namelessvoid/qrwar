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
			GuiHandler(qrw::Engine* _engine, sf::RenderWindow* _renderwindow);
			~GuiHandler();

			sf::RenderWindow* getRenderWindow();

			void display(sf::RenderWindow& _renderwindow);

			inline bool guiVisible() { return _visible; }

			/**
			 * Toggle the gui. If gui will be hidden, save the visibility stats of the windows so they can be restored
			 * when the gui is set visible again.
			 */
			void toggleGui();

			inline bool getQuit() { return _quit; }
			inline void setQuit(bool quit) { this->_quit = quit; }
			inline void doQuit() { this->_quit = true; }

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

			qrw::Engine* _engine;
			BoardWidget* _boardwidget;

			sf::Clock _clock;

			sf::RenderWindow* _renderwindow;

			sfg::Window::Ptr _windows[NUMEROFWINDOWS];
			bool _visiblestats[NUMEROFWINDOWS];
			DeployWindow* _deploywindow;
			IngameWindow* _ingamewindow;

			sfg::SFGUI _sfgui;
			bool _visible;
			bool _quit;

			class NoSuchWindowException
			{
				public:
					NoSuchWindowException() {}
					~NoSuchWindowException() {}
			};
	};
}
#endif
