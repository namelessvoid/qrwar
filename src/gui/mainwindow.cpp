#include "SFGUI/SFGUI.hpp"

#include "gui/mainwindow.hpp"
#include "gui/guihandler.hpp"

namespace qrw
{
	MainWindow::Ptr MainWindow::Create(GuiHandler* guihandler)
	{
		MainWindow::Ptr window(new MainWindow(guihandler));
		window->SetTitle("Main Menu");

		// Create buttons
		sfg::Button::Ptr quitbutton = sfg::Button::Create("Quit!");
		quitbutton->GetSignal(sfg::Button::OnLeftClick).Connect(
			std::bind(&GuiHandler::doQuit, guihandler));

		sfg::Button::Ptr startbutton = sfg::Button::Create("New Game");
		startbutton->GetSignal(sfg::Button::OnLeftClick).Connect(
			std::bind(&GuiHandler::showStartGameWindow, guihandler));

		sfg::Button::Ptr savegamebutton = sfg::Button::Create("Savegames");

		sfg::Button::Ptr settingsbutton = sfg::Button::Create("Settings");
		settingsbutton->GetSignal(sfg::Button::OnLeftClick).Connect(
			std::bind(&GuiHandler::showSettingsWindow, guihandler));

		sfg::Button::Ptr creditsbutton = sfg::Button::Create("Credits");

		// Create layout
		sfg::Table::Ptr maincontainer = sfg::Table::Create();
		int options = sfg::Table::FILL | sfg::Table::EXPAND;
		maincontainer->Attach(startbutton,		sf::Rect<sf::Uint32>(0, 0,  10, 10), options, options);
		maincontainer->Attach(savegamebutton,	sf::Rect<sf::Uint32>(0, 10, 10, 10), options, options);
		maincontainer->Attach(settingsbutton,	sf::Rect<sf::Uint32>(0, 20, 10, 10), options, options);
		maincontainer->Attach(creditsbutton,	sf::Rect<sf::Uint32>(0, 30, 10, 10), options, options);
		maincontainer->Attach(quitbutton,		sf::Rect<sf::Uint32>(0, 40, 10, 10), options, options);
		window->Add(maincontainer);

		window->SetAllocation(sf::FloatRect(0.0, 0.0, 200.0, 300.0));
		return window;
	}

	MainWindow::MainWindow(GuiHandler* guihandler, int style)
		: Window(style),
		  guihandler(guihandler)
	{
	}
}
