#include "game/gui/victorydialog.hpp"

#include "gui/ng/text.hpp"
#include "gui/ng/button.hpp"

namespace qrw {

VictoryDialog::VictoryDialog()
{
	setAnchor({0.5f, 0.5f});
	setParentAnchor({0.5f, 0.5f});
	setSize({300, 250});

	// Winner labels
	namelessgui::Text* victoryText = new namelessgui::Text();
	victoryText->setText("Victory!");
	victoryText->setCharacterSize(40);
	victoryText->setAnchor({0.5f, 0});
	victoryText->setParentAnchor({0.5f, 0});
	addWidget(victoryText);

	m_winnerNameText = new namelessgui::Text();
	m_winnerNameText->setText("Winner");
	m_winnerNameText->setAnchor({0.5f, 0});
	m_winnerNameText->setParentAnchor({0.5f, 0});
	m_winnerNameText->setPosition({0, victoryText->getSize().y + 15});
	addWidget(m_winnerNameText);

	// Loser labels
	namelessgui::Text* loserText = new namelessgui::Text();
	loserText->setText("Defeat!");
	loserText->setCharacterSize(40);
	loserText->setAnchor({0.5f, 0});
	loserText->setParentAnchor({0.5f, 0.4f});
	addWidget(loserText);

	m_loserNameText = new namelessgui::Text();
	m_loserNameText->setText("Loser");
	m_loserNameText->setAnchor({0.5f, 0});
	m_loserNameText->setParentAnchor({0.5f, 0.4f});
	m_loserNameText->setPosition({0, loserText->getSize().y + 15});
	addWidget(m_loserNameText);

	// Close button
	namelessgui::Button* closeButton = new namelessgui::Button();
	closeButton->setText("End Skirmish");
	closeButton->setAnchor({1, 1});
	closeButton->setParentAnchor({1, 1});
	closeButton->setSize({296, closeButton->getSize().y});
	closeButton->setRelativePosition({-2, -2});
	closeButton->signalClicked.connect(std::bind(&VictoryDialog::slotCloseClicked, this));
	addWidget(closeButton);
}

void VictoryDialog::setWinnerName(const std::string &name)
{
	m_winnerNameText->setText(name);
}

void VictoryDialog::setLoserName(const std::string &name)
{
	m_loserNameText->setText(name);
}

void VictoryDialog::slotCloseClicked()
{
	signalCloseClicked.emit();
}

}
