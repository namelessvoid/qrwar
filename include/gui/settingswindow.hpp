#ifndef QRW_SETTINGSWINDOW_HPP
#define QRW_SETTINGSWINDOW_HPP

#include <SFGUI/Window.hpp>


namespace qrw
{
	class SettingsWindow : public sfg::Window
	{
		public:
			typedef std::shared_ptr<SettingsWindow> Ptr;
			typedef std::shared_ptr<const SettingsWindow> PtrConst;

			static Ptr Create();

			void hide();

		protected:
			SettingsWindow(int style = BACKGROUND);

		private:
	};
}

#endif