#include "gui/settingswindow.hpp"

#include <string>
#include <memory>

#include <SFGUI/SFGUI.hpp>

#include "config/settings.hpp"

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

		sfg::Button::Ptr applybutton = sfg::Button::Create("Save");
		applybutton->GetSignal(sfg::Button::OnLeftClick).Connect(
			std::bind(&SettingsWindow::save, window));

		// Create widgets
		sfg::Label::Ptr tilesetlabel = sfg::Label::Create("Tileset path:");
		sfg::Entry::Ptr tilesetentry = sfg::Entry::Create();
		tilesetentry->SetId("tilesetentry");

		sfg::CheckButton::Ptr fullscreenbutton = sfg::CheckButton::Create("Fullscreen");
		fullscreenbutton->SetId("fullscreenbutton");

		// Create layout
		sfg::Table::Ptr maincontainer = sfg::Table::Create();
		int options = sfg::Table::FILL | sfg::Table::EXPAND;

		maincontainer->Attach(fullscreenbutton, sf::Rect<sf::Uint32>(1, 3, 2, 1), options, options);
		maincontainer->Attach(tilesetlabel, sf::Rect<sf::Uint32>(1, 4, 1, 1), options, options);
		maincontainer->Attach(tilesetentry, sf::Rect<sf::Uint32>(2, 4, 4, 1), options, options);
		maincontainer->Attach(cancelbutton, sf::Rect<sf::Uint32>(5, 5, 1, 1), options, options);
		maincontainer->Attach(applybutton, 	sf::Rect<sf::Uint32>(4, 5, 1, 1), options, options);

		window->Add(maincontainer);

		window->SetAllocation(sf::FloatRect(200, 0, 350, 100));
		window->Show(false);

		// Fill widgets with values from Settings
		Settings* settings = Settings::getInstance();
		tilesetentry->SetText(settings->getTilesetPath());
		fullscreenbutton->SetActive(settings->getFullscreen());

		return window;
	}

	void SettingsWindow::hide()
	{
		Show(false);
	}

	void SettingsWindow::save()
	{
		std::string tilesetpath = (std::static_pointer_cast<sfg::Entry>(sfg::Widget::GetWidgetById("tilesetentry")))->GetText();
		bool fullscreen = (std::static_pointer_cast<sfg::CheckButton>(sfg::Widget::GetWidgetById("fullscreenbutton")))->IsActive();

		Settings* settings = Settings::getInstance();
		settings->setTilesetPath(tilesetpath);
		settings->setFullscreen(fullscreen);

		settings->saveToFile();

		hide();
	}
}
