#include <stdio.h>

#include <SFGUI/Button.hpp>
#include <SFGUI/Table.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Separator.hpp>

#include "tostring.hpp"
#include "gui/ingamewindow.hpp"
#include "gui/cursor.hpp"
#include "gui/imagemanager.hpp"
#include "gui/texturemanager.hpp"
#include "gui/guihandler.hpp"

namespace qrw
{
	IngameWindow::IngameWindow(Engine* engine, GuiHandler* guihandler)
	: engine(engine),
	  guihandler(guihandler),
	  endturnbutton(guihandler->getRenderWindow())
	{
		TextureManager* texmgr = TextureManager::getInstance();
		endturnbutton.setText("End turn!");
		endturnbutton.setTextures(texmgr->getTexture("nextbutton"),
			texmgr->getTexture("nextbutton_active"),
			texmgr->getTexture("nextbutton_hover"));
		endturnbutton.setPosition(sf::Vector2f(700, 560));
		endturnbutton.setScale(sf::Vector2f(1, 1));
		endturnbutton.signalclicked.connect(
			std::bind(&IngameWindow::changeplayerbuttonClicked, this));
	}

	IngameWindow::~IngameWindow()
	{}
	void IngameWindow::update()
	{

	}

	sf::Vector2f IngameWindow::getSize()
	{
		return sf::Vector2f(0, 0);
	}

	void IngameWindow::handleEvent(const sf::Event& event)
	{
		endturnbutton.handleEvent(event);
	}

	void IngameWindow::draw(sf::RenderTarget& target, sf::RenderStates) const
	{
		target.draw(endturnbutton);
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
}

