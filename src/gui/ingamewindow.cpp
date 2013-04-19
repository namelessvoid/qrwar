#include <SFGUI/Button.hpp>

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
		sfg::Button::Ptr endturnbutton = sfg::Button::Create("End Turn!");
		endturnbutton->GetSignal(sfg::Button::OnLeftClick).Connect(&Engine::endTurn, engine);
		window->Add(endturnbutton);
		window->SetAllocation(sf::FloatRect(windowsize.x - 100, 0, 100, windowsize.y));
		return window;
	}

	sf::Vector2f IngameWindow::getSize()
	{
		return sf::Vector2f(GetAllocation().width, GetAllocation().height);
	}
}

