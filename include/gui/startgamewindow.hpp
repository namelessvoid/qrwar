#ifndef QRW_STARTGAMEWINDOW_HPP
#define QRW_STARTGAMEWINDOW_HPP

#include <SFGUI/Window.hpp>
#include <SFGUI/SharedPtr.hpp>

#include "engine/engine.hpp"
#include "gui/guihandler.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/placeunitwindow.hpp"

namespace qrw
{
	class StartGameWindow : public sfg::Window
	{
		public:
			typedef sfg::SharedPtr<StartGameWindow> Ptr;
			typedef sfg::SharedPtr<const StartGameWindow> PtrConst;

			static Ptr Create(Engine* engine, IngameWindow::Ptr ingamewindow,
				PlaceUnitWindow::Ptr placeunitwindow, GuiHandler* guihandler);

		protected:
			StartGameWindow(Engine* engine, IngameWindow::Ptr ingamewindow,
				PlaceUnitWindow::Ptr placeunitwindow, GuiHandler* guihandler,
				int style = BACKGROUND);

		private:
			void hide();
			void startGame();
			Engine* engine;
			GuiHandler* guihandler;
			IngameWindow::Ptr ingamewindow;
			PlaceUnitWindow::Ptr placeunitwindow;
	};
}

#endif