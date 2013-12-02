#include <SFGUI/SFGUI.hpp>

#include "gui/settingswindow.hpp"

namespace qrw
{
	SettingsWindow::Ptr SettingsWindow::Create()
	{
		SettingsWindow::Ptr window(new SettingsWindow());
		window->SetTitle("Main Menu");

		// Create buttons
		sfg::Button::Ptr cancelbutton = sfg::Button::Create("Cancel");
		sfg::Button::Ptr applybutton = sfg::Button::Create("Apply");

		// Create layout
		sfg::Table::Ptr maincontainer = sfg::Table::Create();
		int options = sfg::Table::FILL | sfg::Table::EXPAND;
		maincontainer->Attach(cancelbutton, sf::Rect<sf::Uint32>(5, 5, 1, 1), options, options);
		maincontainer->Attach(applybutton, 	sf::Rect<sf::Uint32>(4, 5, 1, 1), options, options);
		// maincontainer->Attach(startbutton,		sf::Rect<sf::Uint32>(0, 0,  10, 10), options, options);

		window->Add(maincontainer);

		window->SetAllocation(sf::FloatRect(200, 0, 350, 100));
		window->Show(false);
		return window;
	}

	SettingsWindow::SettingsWindow(int style)
		: Window(style)
	{
	}
}