#include <stdio.h>

#include "gui/guihandler.hpp"
#include "gui/mainwindow.hpp"
#include "gui/startgamewindow.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/cursor.hpp"

namespace qrw
{
	GuiHandler::GuiHandler(qrw::Engine* engine, sf::Vector2f windowsize)
		: engine(engine),
		  sfgui(sfg::SFGUI()),
		  visible(true),
		  quit(false),
		  windowsize(windowsize)
	{
		// Set up objects that need reference on board instance.
		boardrenderer.setBoard(engine->getBoard());
		Cursor::getCursor()->setBoard(engine->getBoard());
		ingamewindow = new IngameWindow(engine);
		placeunitwindow = PlaceUnitWindow::Create(engine);
		
		windows[MAINWINDOW] = MainWindow::Create(this);
		windows[STARTGAMEWINDOW] = StartGameWindow::Create(engine, ingamewindow,
			placeunitwindow, this);
		windows[LOADGANEWINDO] = sfg::Window::Create();
		windows[SETTINGSWINDOW] = sfg::Window::Create();
		windows[CREDITSWINDOW] = sfg::Window::Create();

		this->Add(placeunitwindow);
		this->Add(windows[MAINWINDOW]);
		this->Add(windows[STARTGAMEWINDOW]);
	}

	GuiHandler::~GuiHandler()
	{
		delete ingamewindow;
		ingamewindow = NULL;
	}

	void GuiHandler::display(sf::RenderTarget& rendertarget)
	{
		rendertarget.draw(boardrenderer);
		sfgui.Display(rendertarget);
		rendertarget.draw(*(sf::Drawable*)ingamewindow);
	}

	void GuiHandler::toggleGui()
	{
		if(visible)
			// Save visibility stats and make invisile
			for(int i = 0; i < NUMEROFWINDOWS; ++i)
			{
				visiblestats[i] = windows[i]->IsGloballyVisible();
				windows[i]->Show(false);
			}
		// restore visibilities
		else
			for(int i = 0; i < NUMEROFWINDOWS; ++i)
				windows[i]->Show(visiblestats[i]);
		visible = !visible;
	}

	void GuiHandler::showStartGameWindow()
	{
		windows[STARTGAMEWINDOW]->Show(true);
	}

	sfg::Window::Ptr GuiHandler::getWindowById(int id)
	{
		if(id < 0 || id > NUMEROFWINDOWS)
			throw NoSuchWindowException();
		return windows[id];
	}

	void GuiHandler::HandleEvent(const sf::Event& event)
	{
		// Toggle gui
		if(event.type == sf::Event::KeyPressed)
			if(event.key.code == sf::Keyboard::F1)
				toggleGui();
		// Let the gui handle the event
		if(guiVisible())
			sfg::Desktop::HandleEvent(event);
		else
		{
			ingamewindow->handleEvent(event);
			placeunitwindow->HandleEvent(event);
			if(event.type == sf::Event::KeyPressed)
			{
				qrw::Cursor* cursor = qrw::Cursor::getCursor();
				qrw::Cursor* childcursor = cursor->getChild();

				if(event.key.code == sf::Keyboard::Up)
					cursor->move(0, -1);
				else if(event.key.code == sf::Keyboard::Down)
					cursor->move(0, 1);
				else if(event.key.code == sf::Keyboard::Right)
					cursor->move(1, 0);
				else if(event.key.code == sf::Keyboard::Left)
					cursor->move(-1, 0);
				else if(event.key.code == sf::Keyboard::Escape)
					cursor->despawnChild();
				else if(event.key.code == sf::Keyboard::Return)
				{
					if(engine->getStatus() == EES_PREPARE)
					{
						placeunitwindow->placeUnitAtCursor();
					}
					else if(childcursor == 0)
					{
						cursor->spawnChild();
					}
					else if(childcursor != 0)
					{
						// Move a unit
						int moveresult = engine->moveUnit(cursor->getPosition().x, cursor->getPosition().y,
							childcursor->getPosition().x, childcursor->getPosition().y);
						printf("moveresult: %i\n", moveresult);
						if(moveresult == 0 || moveresult == -8 || moveresult == -9)
						{
							cursor->setPosition(childcursor->getPosition());
							cursor->despawnChild();
						}
					}
				}
				ingamewindow->update();
			}
		}
	}
}