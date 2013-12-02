#ifndef QRW_SETTINGSWINDOW_HPP
#define QRW_SETTINGSWINDOW_HPP

#include <SFGUI/Window.hpp>
#include <SFGUI/SharedPtr.hpp>


namespace qrw
{
	class SettingsWindow : public sfg::Window
	{
		public:
			typedef sfg::SharedPtr<SettingsWindow> Ptr;
			typedef sfg::SharedPtr<const SettingsWindow> PtrConst;

			static Ptr Create();

			void hide();

		protected:
			SettingsWindow(int style = BACKGROUND);

		private:
	};
}

#endif