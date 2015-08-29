#ifndef QRW_CONFIRMATIONDIALOG_H
#define QRW_CONFIRMATIONDIALOG_H

#include <string>

#include "gui/ng/window.hpp"
#include "gui/ng/label.hpp"
#include "gui/ng/button.hpp"

namespace namelessgui
{

class ConfirmationDialog : public Window
{
public:
	ConfirmationDialog(const std::string& text);

	Signal<> signalYesClicked;
	Signal<> signalNoClicked;

private:
	void slotYesClicked();
	void slotNoClicked();

	Label* _label;
	Button* _yesButton;
	Button* _noButton;
};

} // namespace namelessgui

#endif // CQRW_ONFIRMATIONDIALOG_H
