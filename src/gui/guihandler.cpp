#include "engine/engine.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "gui/guihandler.hpp"
#include "gui/boardwidget.hpp"
#include "gui/mainwindow.hpp"
#include "gui/settingswindow.hpp"
#include "gui/startgamewindow.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/deploywindow.hpp"
#include "gui/cursor.hpp"
#include "gui/animation.hpp"

namespace qrw
{
	GuiHandler::GuiHandler(qrw::Engine* engine, sf::RenderWindow* renderwindow)
		: _engine(engine),
		  _renderwindow(renderwindow),
		  _sfgui(sfg::SFGUI()),
		  _visible(true),
		  _quit(false)
	{
		// Set up objects that need reference on board instance.
		// TODO: dynamic size
		Cursor::getCursor()->setBoard(engine->getBoard());
		_ingamewindow = new IngameWindow(engine, this);
		_ingamewindow->setVisible(false);
		_deploywindow = new DeployWindow(engine, this, _ingamewindow);
		_deploywindow->setVisible(false);
		_boardwidget = new BoardWidget(this, engine, 620, 600);
		_boardwidget->setBoard(engine->getBoard());

		_windows[MAINWINDOW] = MainWindow::Create(this);
		_windows[STARTGAMEWINDOW] = StartGameWindow::Create(engine, _ingamewindow,
			_deploywindow, _boardwidget, this);
		_windows[LOADGAMEWINDOW] = sfg::Window::Create();
		_windows[SETTINGSWINDOW] = SettingsWindow::Create();
		_windows[CREDITSWINDOW] = sfg::Window::Create();

		this->Add(_windows[MAINWINDOW]);
		this->Add(_windows[STARTGAMEWINDOW]);
		this->Add(_windows[SETTINGSWINDOW]);
	}

	GuiHandler::~GuiHandler()
	{
		// TODO: delete all member variables!
	}

	void GuiHandler::display(sf::RenderWindow& renderwindow)
	{
		renderwindow.draw(*(namelessgui::Widget*)_boardwidget);

		sf::View gameView = renderwindow.getView();
		sf::View guiView(sf::FloatRect(0, 0, renderwindow.getSize().x, renderwindow.getSize().y));
		renderwindow.setView(guiView);

		renderwindow.draw(*(sf::Drawable*)_ingamewindow);
		renderwindow.draw(*(sf::Drawable*)_deploywindow);
		Animation::renderAll(renderwindow, _clock.restart());
		_sfgui.Display(renderwindow);

		renderwindow.setView(gameView);
	}

	sf::RenderWindow* GuiHandler::getRenderWindow()
	{
		return _renderwindow;
	}

	void GuiHandler::toggleGui()
	{
		if(_visible)
			// Save visibility stats and make invisile
			for(int i = 0; i < NUMEROFWINDOWS; ++i)
			{
				_visiblestats[i] = _windows[i]->IsGloballyVisible();
				_windows[i]->Show(false);
			}
		// restore visibilities
		else
			for(int i = 0; i < NUMEROFWINDOWS; ++i)
				_windows[i]->Show(_visiblestats[i]);
		_visible = !_visible;
	}

	void GuiHandler::showStartGameWindow()
	{
		hideAllWindows();
		_windows[STARTGAMEWINDOW]->Show(true);
	}

	void GuiHandler::showSettingsWindow()
	{
		hideAllWindows();
		_windows[SETTINGSWINDOW]->Show(true);
	}

	sfg::Window::Ptr GuiHandler::getWindowById(int id)
	{
		if(id < 0 || id > NUMEROFWINDOWS)
			throw NoSuchWindowException();
		return _windows[id];
	}

	DeployWindow* GuiHandler::getDeployWindow()
	{
		return _deploywindow;
	}

	IngameWindow* GuiHandler::getIngameWindow()
	{
		return _ingamewindow;
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
			_ingamewindow->handleEvent(event);
		}
		else
		{
			_ingamewindow->handleEvent(event);
			_deploywindow->handleEvent(event);
			_boardwidget->handleEvent(event);
		}
		_ingamewindow->update();
	}

	void GuiHandler::hideAllWindows()
	{
		// Hide all except ID o (MainWindow)
		for(int i = 1; i < NUMEROFWINDOWS; ++i)
			_windows[i]->Show(false);
	}
}
