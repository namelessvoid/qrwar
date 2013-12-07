#ifndef QRW_MAINWINDOW_HPP
#define QRW_MAINWINDOW_HPP

#include <SFGUI/Window.hpp>

#include "gui/guihandler.hpp"

namespace qrw
{
	class MainWindow : public sfg::Window
	{
		public:
			typedef std::shared_ptr<MainWindow> Ptr;
			typedef std::shared_ptr<const MainWindow> PtrConst;

			static Ptr Create(GuiHandler* guihandler);
		
		protected:
			MainWindow(GuiHandler* guihandler, int style = BACKGROUND);

		private:
			GuiHandler* guihandler;
	};
}

#endif