#ifndef QRW_INGAMEWINDOW_HPP
#define QRW_INGAMEWINDOW_HPP

#include <SFGUI/Window.hpp>
#include <SFGUI/SharedPtr.hpp>

#include "engine/engine.hpp"

namespace qrw
{
	class IngameWindow : sfg::Window
	{
		public:
			typedef sfg::SharedPtr<IngameWindow> Ptr;
			typedef sfg::SharedPtr<const IngameWindow> PtrConst;

			static Ptr Create(Engine* engine);

		protected:
			IngameWindow(Engine* engine);

		private:
			Engine* engine;
	};
}

#endif