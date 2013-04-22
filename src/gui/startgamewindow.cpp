#include <stdio.h>

#include <SFGUI/Button.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/SpinButton.hpp>
#include <SFGUI/Image.hpp>

#include "gui/startgamewindow.hpp"
#include "engine/unit.hpp"

namespace qrw
{
	StartGameWindow::Ptr StartGameWindow::Create(Engine* engine, IngameWindow::Ptr ingamewindow)
	{
		Ptr window(new StartGameWindow(engine, ingamewindow));
		window->SetTitle("Start new game");

		sf::Image img;
		img.loadFromFile("./res/img/units/swordman.png");
		sfg::Image::Ptr swordsmanimg = sfg::Image::Create(img);
		img.loadFromFile("./res/img/units/archer.png");
		sfg::Image::Ptr archerimg = sfg::Image::Create(img);
		img.loadFromFile("./res/img/units/spearman.png");
		sfg::Image::Ptr spearmanimg = sfg::Image::Create(img);

		sfg::Label::Ptr playeronelabel = sfg::Label::Create("Player 1");
		sfg::Label::Ptr playertwolabel = sfg::Label::Create("Player 2");

		sfg::SpinButton::Ptr p1swordspin = sfg::SpinButton::Create(0, 100, 1);
		p1swordspin->SetValue(0);
		p1swordspin->SetId("p1swordspin");
		sfg::SpinButton::Ptr p1archspin  = sfg::SpinButton::Create(0, 100, 1);
		p1archspin->SetValue(0);
		p1archspin->SetId("p1archspin");
		sfg::SpinButton::Ptr p1spearspin = sfg::SpinButton::Create(0, 100, 1);
		p1spearspin->SetValue(0);
		p1spearspin->SetId("p1spearspin");
		sfg::SpinButton::Ptr p2swordspin = sfg::SpinButton::Create(0, 100, 1);
		p2swordspin->SetValue(0);
		p2swordspin->SetId("p2swordspin");
		sfg::SpinButton::Ptr p2archspin  = sfg::SpinButton::Create(0, 100, 1);
		p2archspin->SetValue(0);
		p2archspin->SetId("p2archspin");
		sfg::SpinButton::Ptr p2spearspin = sfg::SpinButton::Create(0, 100, 1);
		p2spearspin->SetValue(0);
		p2spearspin->SetId("p2spearspin");

		sfg::Label::Ptr boardwidthlabel = sfg::Label::Create("Board X");
		sfg::Label::Ptr boardheightlabel = sfg::Label::Create("Borad Y");

		sfg::SpinButton::Ptr boardwidthspin = sfg::SpinButton::Create(3, 20, 1);
		boardwidthspin->SetValue(3);
		boardwidthspin->SetId("boardwidthspin");
		sfg::SpinButton::Ptr boardheightspin = sfg::SpinButton::Create(3, 20, 1);
		boardheightspin->SetValue(3);
		boardheightspin->SetId("boardheightspin");

		sfg::Button::Ptr closebutton = sfg::Button::Create("Close");
		closebutton->GetSignal(sfg::Button::OnLeftClick).Connect(&StartGameWindow::hide, &(*window));
		sfg::Button::Ptr startbutton = sfg::Button::Create("Start game");
		startbutton->GetSignal(sfg::Button::OnLeftClick).Connect(&StartGameWindow::startGame, &(*window));

		sfg::Table::Ptr maincontainer = sfg::Table::Create();
		int options = sfg::Table::FILL | sfg::Table::EXPAND;
		// Images
		maincontainer->Attach(swordsmanimg, sf::Rect<sf::Uint32>(0, 1, 1, 1));
		maincontainer->Attach(archerimg, sf::Rect<sf::Uint32>(0, 2, 1, 1));
		maincontainer->Attach(spearmanimg, sf::Rect<sf::Uint32>(0, 3, 1, 1));
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
		// Board settings
		maincontainer->Attach(boardwidthlabel, sf::Rect<sf::Uint32>(1, 4, 1, 1), options, options);
		maincontainer->Attach(boardheightlabel, sf::Rect<sf::Uint32>(2, 4, 1, 1), options, options);
		maincontainer->Attach(boardwidthspin, sf::Rect<sf::Uint32>(1, 5, 1, 1), options, options);
		maincontainer->Attach(boardheightspin, sf::Rect<sf::Uint32>(2, 5, 1, 1), options, options);
		// Buttons
		maincontainer->Attach(closebutton, sf::Rect<sf::Uint32>(0, 6, 2, 1), options, options);
		maincontainer->Attach(startbutton, sf::Rect<sf::Uint32>(2, 6, 1, 1), options, options);


		window->Add(maincontainer);
		window->SetAllocation(sf::FloatRect(200, 0, 350, 100));
		window->Show(false);
		return window;
	}

	StartGameWindow::StartGameWindow(Engine* engine, IngameWindow::Ptr ingamewindow, int style)
	: Window(style),
	  engine(engine),
	  ingamewindow(ingamewindow)
	{}

	void StartGameWindow::startGame()
	{
		// Init engine
		int width = sfg::DynamicPointerCast<sfg::SpinButton>(sfg::Widget::GetWidgetById("boardwidthspin"))->GetValue();
		int height = sfg::DynamicPointerCast<sfg::SpinButton>(sfg::Widget::GetWidgetById("boardheightspin"))->GetValue();
		engine->init(width, height);

		// Create unit arrays for engine.
		int p1units[EUT_NUMBEROFUNITTYPES];
		p1units[EUT_SWORDMAN] = sfg::DynamicPointerCast<sfg::SpinButton>(sfg::Widget::GetWidgetById("p1swordspin"))->GetValue();
		p1units[EUT_ARCHER] = sfg::DynamicPointerCast<sfg::SpinButton>(sfg::Widget::GetWidgetById("p1archspin"))->GetValue();
		p1units[EUT_SPEARMAN] = sfg::DynamicPointerCast<sfg::SpinButton>(sfg::Widget::GetWidgetById("p1spearspin"))->GetValue();

		int p2units[EUT_NUMBEROFUNITTYPES];
		p2units[EUT_SWORDMAN] = sfg::DynamicPointerCast<sfg::SpinButton>(sfg::Widget::GetWidgetById("p2swordspin"))->GetValue();
		p2units[EUT_ARCHER] = sfg::DynamicPointerCast<sfg::SpinButton>(sfg::Widget::GetWidgetById("p2archspin"))->GetValue();
		p2units[EUT_SPEARMAN] = sfg::DynamicPointerCast<sfg::SpinButton>(sfg::Widget::GetWidgetById("p2spearspin"))->GetValue();

		engine->setUnits(p1units, p2units);
		ingamewindow->update();
		hide();
	}

	void StartGameWindow::hide()
	{
		Show(false);
	}
}