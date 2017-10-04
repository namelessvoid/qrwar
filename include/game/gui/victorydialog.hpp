#ifndef QRW_VICTORYDIALOG_HPP
#define QRW_VICTORYDIALOG_HPP

#include "gui/ng/window.hpp"

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

private:
    namelessgui::Text* m_winnerNameText;
    namelessgui::Text* m_loserNameText;
};

}

#endif // QRW_VICTORYDIALOG_HPP
