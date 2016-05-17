#include "gui/ng/confirmationdialog.hpp"

namespace namelessgui
{

ConfirmationDialog::ConfirmationDialog(const std::string& text)
    : _label(new Text()),
	  _yesButton(new Button()),
	  _noButton(new Button())
{
	_label->setText(text);

	setSize({_label->getSize().x + 10, 75.0f});

	_yesButton->setText("Yes");
	_yesButton->setSize({50.0f, 30.0f});
	_yesButton->setAnchor({1.0f, 1.0f});
	_yesButton->setParentAnchor({0.5f, 1.0f});
	_yesButton->setRelativePosition({-5.0f, -5.0f});

	_noButton->setText("No");
	_noButton->setSize({50.0f, 30.0f});
	_noButton->setAnchor({0.0f, 1.0f});
	_noButton->setParentAnchor({0.5f, 1.0f});
	_noButton->setRelativePosition({5.0f, -5.0f});

	_yesButton->signalclicked.connect(std::bind(&ConfirmationDialog::slotYesClicked, this));
	_noButton->signalclicked.connect(std::bind(&ConfirmationDialog::slotNoClicked, this));

	addWidget(_label);
	addWidget(_yesButton);
	addWidget(_noButton);
}

void ConfirmationDialog::slotYesClicked()
{
	signalYesClicked.emit();
	setVisible(false);
}

void ConfirmationDialog::slotNoClicked()
{
	signalNoClicked.emit();
	setVisible(false);
}

} // namespace qrw
