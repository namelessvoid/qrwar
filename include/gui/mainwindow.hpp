#ifndef QRW_MAINWINDOW_HPP
#define QRW_MAINWINDOW_HPP

#include <SFGUI/Window.hpp>
#include <SFGUI/SharedPtr.hpp>

#include "gui/guihandler.hpp"

namespace qrw
{
	class MainWindow : public sfg::Window
	{
		public:
			typedef sfg::SharedPtr<MainWindow> Ptr;
			typedef sfg::SharedPtr<const MainWindow> PtrConst;

			static Ptr Create(GuiHandler* guihandler);
		
		protected:
			MainWindow(GuiHandler* guihandler, int style = BACKGROUND);

		private:
			GuiHandler* guihandler;
	};
}

#endif