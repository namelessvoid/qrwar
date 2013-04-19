#ifndef QRW_STARTGAMEWINDOW_HPP
#define QRW_STARTGAMEWINDOW_HPP

#include <SFGUI/Window.hpp>
#include <SFGUI/SharedPtr.hpp>

#include "engine/engine.hpp"

namespace qrw
{
	class StartGameWindow : public sfg::Window
	{
		public:
			typedef sfg::SharedPtr<StartGameWindow> Ptr;
			typedef sfg::SharedPtr<const StartGameWindow> PtrConst;

			static Ptr Create(Engine* engine);

		protected:
			StartGameWindow(Engine* engine, int style = BACKGROUND);

		private:
			void hide();
			void startGame();
			Engine* engine;


	};
}

#endif