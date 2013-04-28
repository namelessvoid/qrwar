#include <stdio.h>

#include <SFGUI/Table.hpp>
#include <SFGUI/ToggleButton.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/ComboBox.hpp>

#include "tostring.hpp"
#include "gui/cursor.hpp"
#include "gui/placeunitwindow.hpp"

namespace qrw
{
	PlaceUnitWindow::PlaceUnitWindow(Engine* engine)
	: Window(TOPLEVEL),
		engine(engine)
	{
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
		{
			p1units[i] = 0;
			p2units[i] = 0;
		}
	}

	PlaceUnitWindow::Ptr PlaceUnitWindow::Create(Engine* engine)
	{
		PlaceUnitWindow::Ptr window(new PlaceUnitWindow(engine));

		// Load images
		sf::Image swordimg;
		swordimg.loadFromFile("./res/img/units/swordman.png");
		sf::Image archerimg;
		archerimg.loadFromFile("./res/img/units/archer.png");
		sf::Image spearimg;
		spearimg.loadFromFile("./res/img/units/spearman.png");

		// sfg::Label::Ptr p1label = sfg::Label::Create(engine->getPlayer(0)->getName());
		// sfg::Button::Ptr p1swordbutton = sfg::Button::Create("blabla");
		// p1swordbutton->SetImage(sfg::Image::Create(swordimg));
		// sfg::Button::Ptr p1archerbutton = sfg::Button::Create("blabla");
		// p1archerbutton->SetImage(sfg::Image::Create(archerimg));
		// // p1archerbutton->SetGroup(buttongroup);
		// sfg::Button::Ptr p1spearbutton = sfg::Button::Create("blabla");
		// p1spearbutton->SetImage(sfg::Image::Create(spearimg));

		// sfg::Label::Ptr p2label = sfg::Label::Create(engine->getPlayer(1)->getName());
		// sfg::Button::Ptr p2swordbutton = sfg::Button::Create("blabla");
		// p2swordbutton->SetImage(sfg::Image::Create(swordimg));
		// sfg::Button::Ptr p2archerbutton = sfg::Button::Create("blabla");
		// p2archerbutton->SetImage(sfg::Image::Create(archerimg));
		// sfg::Button::Ptr p2spearbutton = sfg::Button::Create("blabla");
		// p2spearbutton->SetImage(sfg::Image::Create(spearimg));

		sfg::ComboBox::Ptr playerbox = sfg::ComboBox::Create();
		playerbox->SetId("playerbox");
		playerbox->AppendItem(engine->getPlayer(0)->getName());
		playerbox->AppendItem(engine->getPlayer(1)->getName());
		playerbox->GetSignal(sfg::ComboBox::OnSelect).Connect(&PlaceUnitWindow::update, &(*window));
		playerbox->SelectItem(0);

		sfg::ComboBox::Ptr unitbox = sfg::ComboBox::Create();
		unitbox->SetId("unitbox");
		unitbox->AppendItem("Swordsman");
		unitbox->AppendItem("Spearman");
		unitbox->AppendItem("Archer");
		unitbox->SelectItem(0);

		sfg::Label::Ptr advicelabel = sfg::Label::Create("Select player and unit.\nPlace cursor via arrow keys and\nhit return to deploy unit.");

		sfg::Button::Ptr startgamebutton = sfg::Button::Create("Start game");
		startgamebutton->GetSignal(sfg::Button::OnLeftClick).Connect(&PlaceUnitWindow::startgamebuttonClicked, &(*window));

		sfg::Table::Ptr maincontainer = sfg::Table::Create();
		int options = sfg::Table::FILL | sfg::Table::EXPAND;
		// maincontainer->Attach(p1label, sf::Rect<sf::Uint32>(0, 0, 1, 1), options, options);
		// maincontainer->Attach(p1swordbutton, sf::Rect<sf::Uint32>(1, 0, 1, 1), options, options);
		// maincontainer->Attach(p1archerbutton, sf::Rect<sf::Uint32>(2, 0, 1, 1), options, options);
		// maincontainer->Attach(p1spearbutton, sf::Rect<sf::Uint32>(3, 0, 1, 1), options, options);

		// maincontainer->Attach(p2label, sf::Rect<sf::Uint32>(0, 1, 1, 1), options, options);
		// maincontainer->Attach(p2swordbutton, sf::Rect<sf::Uint32>(1, 1, 1, 1), options, options);
		// maincontainer->Attach(p2archerbutton, sf::Rect<sf::Uint32>(2, 1, 1, 1), options, options);
		// maincontainer->Attach(p2spearbutton, sf::Rect<sf::Uint32>(3, 1, 1, 1), options, options);

		maincontainer->Attach(advicelabel, sf::Rect<sf::Uint32>(0, 0, 1, 1), options, options);
		maincontainer->Attach(playerbox, sf::Rect<sf::Uint32>(0, 1, 1, 1), options, options);
		maincontainer->Attach(unitbox, sf::Rect<sf::Uint32>(2, 1, 1, 1), options, options);
		maincontainer->Attach(startgamebutton, sf::Rect<sf::Uint32>(2, 2, 1, 1));

		window->SetTitle("Deploy your units!");
		window->Add(maincontainer);
		window->Show(false);
		// window->SetAllocation(sf::FloatRect(0, 0, 160, 120));
		return window;
	}

	void PlaceUnitWindow::placeUnitAtCursor()
	{
		// Get playerid and unittype
		int playerid = getSelectedPlayerId();
		Player* player = engine->getPlayer(playerid);
		UNITTYPES unittype = (UNITTYPES)getSelectedUnitType();

		// Check if all units of this type have been placed.
		if(playerid == 0 && p1units[unittype] <= player->getNumberOfUnits()[unittype])
			return;
		else if(playerid == 1 && p2units[unittype] <= player->getNumberOfUnits()[unittype])
			return;

		Cursor* cursor = Cursor::getCursor();
		int x = cursor->getPosition().x;
		int y = cursor->getPosition().y;
		engine->placeUnit(x, y, playerid, unittype);

		update();
	}

	void PlaceUnitWindow::setPlayerUnits(int p1units[], int p2units[])
	{
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
		{
			this->p1units[i] = p1units[i];
			this->p2units[i] = p2units[i];
		}
	}

	void PlaceUnitWindow::update()
	{
		int playerid = getSelectedPlayerId();
		int unitid = getSelectedUnitType();

		// Update text of unitbox
		sfg::ComboBox::Ptr unitbox = sfg::DynamicPointerCast<sfg::ComboBox>(sfg::Widget::GetWidgetById("unitbox"));
		std::string unitboxtext;
		for(int i = 0; i < EUT_NUMBEROFUNITTYPES; ++i)
		{
			unitboxtext = Unit::UNITNAMES[i];
			unitboxtext += " (" + intToString(engine->getPlayer(playerid)->getNumberOfUnits()[i]) + "/";
			if(playerid == 0)
				unitboxtext += intToString(p1units[i]) + ")";
			else
				unitboxtext += intToString(p2units[i]) + ")";
			unitbox->ChangeItem(i, unitboxtext);
		}
	}

	int PlaceUnitWindow::getSelectedPlayerId()
	{
		return (sfg::DynamicPointerCast<sfg::ComboBox>(sfg::Widget::GetWidgetById("playerbox")))->GetSelectedItem();
	}

	int PlaceUnitWindow::getSelectedUnitType()
	{
		return (sfg::DynamicPointerCast<sfg::ComboBox>(sfg::Widget::GetWidgetById("unitbox")))->GetSelectedItem();
	}

	void PlaceUnitWindow::startgamebuttonClicked()
	{
		if(engine->getStatus() == EES_PREPARE)
		{
			printf("PlaceUnitWindow: starting game\n");
			engine->startGame();
			Show(false);
			update();
		}
	}
}