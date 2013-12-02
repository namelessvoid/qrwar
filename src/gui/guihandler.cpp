#include <stdio.h>

#include "gui/guihandler.hpp"
#include "gui/mainwindow.hpp"
#include "gui/settingswindow.hpp"
#include "gui/startgamewindow.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/cursor.hpp"
#include "gui/animation.hpp"

namespace qrw
{
	GuiHandler::GuiHandler(qrw::Engine* engine, sf::Window* renderwindow)
		: engine(engine),
		  sfgui(sfg::SFGUI()),
		  visible(true),
		  quit(false),
		  renderwindow(renderwindow)
	{
		// Set up objects that need reference on board instance.
		// TODO: dynamic size
		Cursor::getCursor()->setBoard(engine->getBoard());
		ingamewindow = new IngameWindow(engine, this);
		ingamewindow->setVisible(false);
		deploywindow = new DeployWindow(engine, this, ingamewindow);
		deploywindow->setVisible(false);
		boardwidget = new BoardWidget(this, engine, 620, 600);
		boardwidget->setBoard(engine->getBoard());

		windows[MAINWINDOW] = MainWindow::Create(this);
		windows[STARTGAMEWINDOW] = StartGameWindow::Create(engine, ingamewindow,
			deploywindow, boardwidget, this);
		windows[LOADGAMEWINDOW] = sfg::Window::Create();
		windows[SETTINGSWINDOW] = SettingsWindow::Create();
		windows[CREDITSWINDOW] = sfg::Window::Create();

		this->Add(windows[MAINWINDOW]);
		this->Add(windows[STARTGAMEWINDOW]);
		this->Add(windows[SETTINGSWINDOW]);
	}

	GuiHandler::~GuiHandler()
	{
		// TODO: delete all member variables!
	}

	void GuiHandler::display(sf::RenderTarget& rendertarget)
	{
		rendertarget.draw(*boardwidget);
		rendertarget.draw(*(sf::Drawable*)ingamewindow);
		rendertarget.draw(*(sf::Drawable*)deploywindow);
		Animation::renderAll(rendertarget, clock.restart());
		sfgui.Display((sf::RenderWindow&)rendertarget);
	}

	sf::Window* GuiHandler::getRenderWindow()
	{
		return renderwindow;
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
		hideAllWindows();
		windows[STARTGAMEWINDOW]->Show(true);
	}

	void GuiHandler::showSettingsWindow()
	{
		hideAllWindows();
		windows[SETTINGSWINDOW]->Show(true);
	}

	sfg::Window::Ptr GuiHandler::getWindowById(int id)
	{
		if(id < 0 || id > NUMEROFWINDOWS)
			throw NoSuchWindowException();
		return windows[id];
	}

	DeployWindow* GuiHandler::getDeployWindow()
	{
		return deploywindow;
	}

	IngameWindow* GuiHandler::getIngameWindow()
	{
		return ingamewindow;
	}

	void GuiHandler::HandleEvent(const sf::Event& event)
	{
		// Toggle gui
		if(event.type == sf::Event::KeyPressed)
			if(event.key.code == sf::Keyboard::F1)
				toggleGui();
		// Let the gui handle the event
		if(guiVisible())
		{
			sfg::Desktop::HandleEvent(event);
			ingamewindow->handleEvent(event);
		}
		else
		{
			ingamewindow->handleEvent(event);
			deploywindow->handleEvent(event);
			boardwidget->handleEvent(event);
		}
		ingamewindow->update();
	}

	void GuiHandler::hideAllWindows()
	{
		for(int i = 0; i < NUMEROFWINDOWS; ++i)
			windows[i]->Show(false);
	}
}