#ifndef QRW_STARTGAMEWINDOW_HPP
#define QRW_STARTGAMEWINDOW_HPP

#include <SFGUI/Window.hpp>

namespace qrw
{
	class Engine;
	class GuiHandler;
	class IngameWindow;
	class DeployWindow;
	class BoardWidget;

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
			Engine* _engine;
			GuiHandler* _guihandler;
			IngameWindow* _ingamewindow;
			DeployWindow* _deploywindow;
			BoardWidget* _boardwidget;
	};
}

#endif
