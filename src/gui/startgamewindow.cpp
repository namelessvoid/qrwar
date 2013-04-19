#include <SFGUI/Button.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/SpinButton.hpp>

#include "gui/startgamewindow.hpp"

namespace qrw
{
	StartGameWindow::Ptr StartGameWindow::Create()
	{
		Ptr window(new StartGameWindow());
		window->SetTitle("Start new game");

		sfg::Label::Ptr playeronelabel = sfg::Label::Create("Player 1");
		sfg::Label::Ptr playertwolabel = sfg::Label::Create("Player 2");

		sfg::SpinButton::Ptr p1swordspin = sfg::SpinButton::Create(0, 100, 1);
		p1swordspin->SetValue(0);
		sfg::SpinButton::Ptr p1archspin  = sfg::SpinButton::Create(0, 100, 1);
		p1archspin->SetValue(0);
		sfg::SpinButton::Ptr p1spearspin = sfg::SpinButton::Create(0, 100, 1);
		p1spearspin->SetValue(0);
		sfg::SpinButton::Ptr p2swordspin = sfg::SpinButton::Create(0, 100, 1);
		p2swordspin->SetValue(0);
		sfg::SpinButton::Ptr p2archspin  = sfg::SpinButton::Create(0, 100, 1);
		p2archspin->SetValue(0);
		sfg::SpinButton::Ptr p2spearspin = sfg::SpinButton::Create(0, 100, 1);
		p2spearspin->SetValue(0);

		sfg::Button::Ptr closebutton = sfg::Button::Create("Close");
		closebutton->GetSignal(sfg::Button::OnLeftClick).Connect(&StartGameWindow::hide, &(*window));
		sfg::Button::Ptr startbutton = sfg::Button::Create("Start game");

		sfg::Table::Ptr maincontainer = sfg::Table::Create();
		int options = sfg::Table::FILL | sfg::Table::EXPAND;
		// Player 1 stuff
		maincontainer->Attach(playeronelabel, sf::Rect<sf::Uint32>(1, 0, 1, 1), options, options);
		maincontainer->Attach(p1swordspin, sf::Rect<sf::Uint32>(1, 1, 1, 1), options, options);
		maincontainer->Attach(p1archspin, sf::Rect<sf::Uint32>(1, 2, 1, 1), options, options);
		maincontainer->Attach(p1spearspin, sf::Rect<sf::Uint32>(1, 3, 1, 1), options, options);
		// Player 2 stuff
		maincontainer->Attach(playertwolabel, sf::Rect<sf::Uint32>(2, 0, 1, 1), options, options);
		maincontainer->Attach(p2swordspin, sf::Rect<sf::Uint32>(2, 1, 1, 1), options, options);
		maincontainer->Attach(p2archspin, sf::Rect<sf::Uint32>(2, 2, 1, 1), options, options);
		maincontainer->Attach(p2spearspin, sf::Rect<sf::Uint32>(2, 3, 1, 1), options, options);
		// Buttons
		maincontainer->Attach(closebutton, sf::Rect<sf::Uint32>(0, 4, 2, 1), options, options);
		maincontainer->Attach(startbutton, sf::Rect<sf::Uint32>(2, 4, 1, 1), options, options);


		window->Add(maincontainer);
		window->SetAllocation(sf::FloatRect(200, 0, 350, 100));
		window->Show(false);
		return window;
	}

	StartGameWindow::StartGameWindow(int style)
	: Window(style)
	{}

	void StartGameWindow::hide()
	{
		Show(false);
	}
}