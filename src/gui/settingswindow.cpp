#include "gui/settingswindow.hpp"

#include <SFGUI/SFGUI.hpp>

namespace qrw
{
	SettingsWindow::SettingsWindow(int style)
		: Window(style)
	{
	}

	SettingsWindow::Ptr SettingsWindow::Create()
	{
		SettingsWindow::Ptr window(new SettingsWindow());
		window->SetTitle("Main Menu");

		// Create buttons
		sfg::Button::Ptr cancelbutton = sfg::Button::Create("Cancel");
		cancelbutton->GetSignal(sfg::Button::OnLeftClick).Connect(
			std::bind(&SettingsWindow::hide, window));

		sfg::Button::Ptr applybutton = sfg::Button::Create("Apply");

		// Create widgets
		sfg::Label::Ptr tilesetlabel = sfg::Label::Create("Tileset path:");
		sfg::Entry::Ptr tilesetentry = sfg::Entry::Create("./res/defaulttileset.xml");

		// Create layout
		sfg::Table::Ptr maincontainer = sfg::Table::Create();
		int options = sfg::Table::FILL | sfg::Table::EXPAND;

		maincontainer->Attach(tilesetlabel, sf::Rect<sf::Uint32>(1, 4, 1, 1), options, options);
		maincontainer->Attach(tilesetentry, sf::Rect<sf::Uint32>(2, 4, 4, 1), options, options);
		maincontainer->Attach(cancelbutton, sf::Rect<sf::Uint32>(5, 5, 1, 1), options, options);
		maincontainer->Attach(applybutton, 	sf::Rect<sf::Uint32>(4, 5, 1, 1), options, options);

		window->Add(maincontainer);

		window->SetAllocation(sf::FloatRect(200, 0, 350, 100));
		window->Show(false);
		return window;
	}

	void SettingsWindow::hide()
	{
		Show(false);
	}
}
