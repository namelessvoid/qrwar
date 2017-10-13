#ifndef QRW_VICTORYDIALOG_HPP
#define QRW_VICTORYDIALOG_HPP

#include "gui/ng/window.hpp"

#include "gui/ng/signal.hpp"

namespace namelessgui {
class Text;
}

namespace qrw {

class VictoryDialog : public namelessgui::Window
{
public:
    VictoryDialog();

    void setWinnerName(const std::string& name);

    void setLoserName(const std::string& name);

	namelessgui::Signal<> signalCloseClicked;

private:
	void slotCloseClicked();

    namelessgui::Text* m_winnerNameText;
    namelessgui::Text* m_loserNameText;
};

}

#endif // QRW_VICTORYDIALOG_HPP
