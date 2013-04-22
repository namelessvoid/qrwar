#include <stdio.h>

#include <SFGUI/Button.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/Label.hpp>

#include "gui/ingamewindow.hpp"

namespace qrw
{
	IngameWindow::IngameWindow(Engine* engine)
	:	Window(BACKGROUND),
		engine(engine)
	{}

	IngameWindow::Ptr IngameWindow::Create(Engine* engine, sf::Vector2f windowsize)
	{
		Ptr window(new IngameWindow(engine));

		sfg::Label::Ptr playernamelabel = sfg::Label::Create("Player");
		playernamelabel->SetId("playernamelabel");

		sfg::Button::Ptr changeplayerbutton = sfg::Button::Create("Change player");
		changeplayerbutton->SetId("changeplayerbutton");
		changeplayerbutton->GetSignal(sfg::Button::OnLeftClick).Connect(&IngameWindow::changeplayerbuttonClicked, &(*window));
		sfg::Button::Ptr startgamebutton = sfg::Button::Create("Start game");
		startgamebutton->SetId("startgamebutton");
		startgamebutton->GetSignal(sfg::Button::OnLeftClick).Connect(&IngameWindow::startgamebuttonClicked, &(*window));
		
		sfg::Table::Ptr maincontainer = sfg::Table::Create();
		int options = sfg::Table::FILL;
		maincontainer->Attach(playernamelabel, sf::Rect<sf::Uint32>(0, 1, 1, 1), options, options);
		maincontainer->Attach(changeplayerbutton, sf::Rect<sf::Uint32>(0, 10, 1, 1), options, options);
		maincontainer->Attach(startgamebutton, sf::Rect<sf::Uint32>(0, 11, 1, 1), options, options);

		window->Add(maincontainer);
		window->SetAllocation(sf::FloatRect(windowsize.x - 180, 0, 180, windowsize.y));
		return window;
	}

	void IngameWindow::update()
	{
		// Update content by player
		sfg::Label::Ptr playernamelabel = sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById("playernamelabel"));
		playernamelabel->SetText(engine->getCurrentPlayer().getName());

		if(engine->getStatus() == EES_PREPARE)
		{
			sfg::DynamicPointerCast<sfg::Button>(sfg::Widget::GetWidgetById("changeplayerbutton"))->SetLabel("Change player");
			sfg::Widget::GetWidgetById("startgamebutton")->Show(true);
		}
		else if (engine->getStatus() == EES_RUNNING)
		{
			sfg::DynamicPointerCast<sfg::Button>(sfg::Widget::GetWidgetById("changeplayerbutton"))->SetLabel("End turn!");
			sfg::Widget::GetWidgetById("startgamebutton")->Show(false);
			// Update content by cursor position
		}
	}

	sf::Vector2f IngameWindow::getSize()
	{
		return sf::Vector2f(GetAllocation().width, GetAllocation().height);
	}

	void IngameWindow::changeplayerbuttonClicked()
	{
		if(engine->getStatus() == EES_RUNNING)
		{
			printf("IngameWindow: end turn\n");
			engine->endTurn();
			update();
		}
	}

	void IngameWindow::startgamebuttonClicked()
	{
		if(engine->getStatus() == EES_PREPARE)
		{
			printf("IngameWindow: starting game\n");
			engine->startGame();
			update();
		}
	}
}

