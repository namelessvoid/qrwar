#include <iostream>

#include "gui/guihandler.hpp"
#include "gui/mainwindow.hpp"

namespace qrw
{
	GuiHandler::GuiHandler()
		: sfgui(sfg::SFGUI()),
		  visible(true),
		  quit(false)
	{
		windows[MAINWINDOW] = MainWindow::Create(this);
		windows[NEWGAMEWINDOW] = sfg::Window::Create();
		windows[LOADGANEWINDO] = sfg::Window::Create();
		windows[SETTINGSWINDOW] = sfg::Window::Create();
		windows[CREDITSWINDOW] = sfg::Window::Create();
		this->Add(windows[MAINWINDOW]);
		// this->Add(windows[NEWGAMEWINDOW]);
	}

	GuiHandler::~GuiHandler()
	{
	}

	void GuiHandler::display(sf::RenderTarget& rendertarget)
	{
		sfgui.Display(rendertarget);
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

	sfg::Window::Ptr GuiHandler::getWindowById(int id)
	{
		if(id < 0 || id > NUMEROFWINDOWS)
			throw NoSuchWindowException();
		return windows[id];
	}
}