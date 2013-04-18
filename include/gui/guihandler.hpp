#ifndef QRW_GUIHANDLER_HPP
#define QRW_GUIHANDLER_HPP

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Window.hpp>

namespace qrw
{
	/**
	 * @brief Enum holding all window ids.
	 */
	enum EW_WINDOWIDS
	{
		MAINWINDOW = 0,
		NEWGAMEWINDOW,
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
			GuiHandler();
			~GuiHandler();

			void display(sf::RenderTarget& rendertarget);

			inline bool guiVisible() { return visible; };

			void toggleGui();

			inline bool getQuit() { return quit; };
			inline void setQuit(bool quit) { this->quit = quit; };
			inline void doQuit() { this->quit = true; };

			sfg::Window::Ptr getWindowById(int id);

		private:
			sfg::Window::Ptr windows[NUMEROFWINDOWS];
			bool visiblestats[NUMEROFWINDOWS];

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