#ifndef QRW_STARTGAMEWINDOW_HPP
#define QRW_STARTGAMEWINDOW_HPP

#include <SFGUI/Window.hpp>

#include "engine/engine.hpp"
#include "gui/guihandler.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/deploywindow.hpp"

namespace qrw
{
	class StartGameWindow : public sfg::Window
	{
		public:
			typedef std::shared_ptr<StartGameWindow> Ptr;
			typedef std::shared_ptr<const StartGameWindow> PtrConst;

			static Ptr Create(Engine* engine, IngameWindow* ingamewindow,
				DeployWindow* deploywindow,
				BoardWidget* boardwidget, GuiHandler* guihandler);

		protected:
			StartGameWindow(Engine* engine, IngameWindow* ingamewindow,
				DeployWindow* deploywindow,
				BoardWidget* boardwidget, GuiHandler* guihandler,
				int style = BACKGROUND);

		private:
			void hide();
			void startGame();
			Engine* engine;
			GuiHandler* guihandler;
			IngameWindow* ingamewindow;
			DeployWindow* deploywindow;
			BoardWidget* boardwidget;
	};
}

#endif