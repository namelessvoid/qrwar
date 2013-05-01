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
	// IngameWindow::Ptr IngameWindow::Create(Engine* engine, sf::Vector2f windowsize)
	// {
	// 	Ptr window(new IngameWindow(engine));

	// 	sfg::Label::Ptr playernamelabel = sfg::Label::Create("Player");
	// 	playernamelabel->SetId("playernamelabel");

	// 	sfg::Button::Ptr changeplayerbutton = sfg::Button::Create("End turn!");
	// 	changeplayerbutton->GetSignal(sfg::Button::OnLeftClick)
	// 		.Connect(&IngameWindow::changeplayerbuttonClicked, &(*window));

	// 	sfg::Image::Ptr unitimage = sfg::Image::Create();
	// 	unitimage->SetId("unitimage");
	// 	sfg::Label::Ptr unitattacklabel = sfg::Label::Create("A: 0");
	// 	unitattacklabel->SetId("unitattacklabel");
	// 	sfg::Label::Ptr unitdefenselabel =  sfg::Label::Create("D: 0");
	// 	unitdefenselabel->SetId("unitdefenselabel");
	// 	sfg::Label::Ptr unithplabel = sfg::Label::Create("H: 0");
	// 	unithplabel->SetId("unithplabel");
	// 	sfg::Label::Ptr terrainattacklabel = sfg::Label::Create("A: 0");
	// 	terrainattacklabel->SetId("terrainattacklabel");
	// 	sfg::Label::Ptr terraindefenselabel = sfg::Label::Create("D: 0");
	// 	terraindefenselabel->SetId("terraindefenselabel");


	// 	sfg::Separator::Ptr sep1 = sfg::Separator::Create(sfg::Separator::HORIZONTAL);
	// 	sfg::Separator::Ptr sep2 = sfg::Separator::Create(sfg::Separator::HORIZONTAL);
		
	// 	sfg::Table::Ptr maincontainer = sfg::Table::Create();
	// 	int options = sfg::Table::FILL;
	// 	maincontainer->Attach(playernamelabel, sf::Rect<sf::Uint32>(0, 0, 2, 1), options, options);
	// 	maincontainer->Attach(sep1, sf::Rect<sf::Uint32>(0, 1, 2, 1), options | sfg::Table::EXPAND, options);
	// 	maincontainer->Attach(unitimage, sf::Rect<sf::Uint32>(0, 1, 1, 2), options, options);
	// 	maincontainer->Attach(unithplabel, sf::Rect<sf::Uint32>(1, 2, 1, 1), options, options);
	// 	maincontainer->Attach(unitattacklabel, sf::Rect<sf::Uint32>(1, 3, 1, 1), options, options);
	// 	maincontainer->Attach(unitdefenselabel, sf::Rect<sf::Uint32>(1, 4, 1, 1), options, options);
	// 	maincontainer->Attach(terrainattacklabel, sf::Rect<sf::Uint32>(1, 5, 1, 1), options, options);
	// 	maincontainer->Attach(terraindefenselabel, sf::Rect<sf::Uint32>(1, 6, 1, 1), options, options);
	// 	maincontainer->Attach(sep2, sf::Rect<sf::Uint32>(0, 9, 2, 1), options | sfg::Table::EXPAND, options);
	// 	maincontainer->Attach(changeplayerbutton, sf::Rect<sf::Uint32>(0, 10, 2, 1), options, options);

	// 	return window;
	// }

	void IngameWindow::update()
	{
		// Update content by player
		// sfg::Label::Ptr playernamelabel = sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById("playernamelabel"));
		// playernamelabel->SetText(engine->getCurrentPlayer().getName());
		// // Update content information about what's under the cursor / child cursor.
		// Cursor* cursor = Cursor::getCursor();
		// if(cursor->getChild())
		// 	cursor = cursor->getChild();
		// Square* sq = engine->getBoard()->getSquare(cursor->getPosition().x, cursor->getPosition().y);
		// Unit* unit = sq->getUnit();
		// Terrain* terrain = sq->getTerrain();

		// if(unit != 0)
		// {
		// 	// TODO: Render unit image
		// 	std::string imgname = "";
		// 	if(engine->getPlayer(0) == unit->getPlayer())
		// 		imgname = "p1";
		// 	else
		// 		imgname = "p2";
			
		// 	switch(unit->getType())
		// 	{
		// 		case EUT_SWORDMAN: imgname += "swordman"; break;
		// 		case EUT_ARCHER: imgname += "archer"; break;
		// 		default: imgname += "spearman"; break;
		// 	}

		// 	sfg::DynamicPointerCast<sfg::Image>(sfg::Widget::GetWidgetById(
		// 		"unitimage"))->SetImage(*(ImageManager::getInstance()
		// 		->getImage(imgname)));

		// 	// Update unit stats
		// 	sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById(
		// 		"unithplabel"))->SetText("H: " + intToString(unit->getHP()));
		// 	sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById(
		// 		"unitattacklabel"))->SetText("A: " + intToString(unit->getAttack()));
		// 	sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById(
		// 		"unitdefenselabel"))->SetText("D: " + intToString(unit->getDefense()));
		// }
		// else
		// {
		// 	sfg::DynamicPointerCast<sfg::Image>(sfg::Widget::GetWidgetById(
		// 		"unitimage"))->SetImage(*(ImageManager::getInstance()
		// 		->getImage("plainsquare")));
		// 	// Update unit stats
		// 	sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById(
		// 		"unithplabel"))->SetText("H: 0");
		// 	sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById(
		// 		"unitattacklabel"))->SetText("A: 0");
		// 	sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById(
		// 		"unitdefenselabel"))->SetText("D: 0");
		// }

		// if(terrain != 0)
		// {
		// 	//TODO:: REnder terrain image
		// 	// Update terrain states
		// 	sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById(
		// 		"terrainattacklabel"))->SetText(
		// 		"A: " + intToString(terrain->getModificator(EM_ATTACK)));
		// 	sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById(
		// 		"terraindefenselabel"))->SetText(
		// 		"D: " + intToString(terrain->getModificator(EM_DEFENSE)));
		// }
		// else
		// {
		// 	// Update terrain states
		// 	sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById(
		// 		"terrainattacklabel"))->SetText("A: 0");
		// 	sfg::DynamicPointerCast<sfg::Label>(sfg::Widget::GetWidgetById(
		// 		"terraindefenselabel"))->SetText("D: 0");
		// }

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
		// printf("rendering ingame window...\n");
		target.draw(endturnbutton);
		// endturnbutton.draw(target);
		// printf("ingame window rendering done!\n");
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

