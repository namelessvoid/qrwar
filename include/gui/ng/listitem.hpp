#ifndef NAMELESSGUI_LISTITEM_HPP
#define NAMELESSGUI_LISTITEM_HPP

#include "spritewidget.hpp"

#include "text.hpp"

namespace namelessgui {

class ListItem : public RectangularWidget
{
public:
    ListItem();

    virtual ~ListItem();

    void setText(const std::string& text) { text_->setText(text); }

    const std::string getText() const { return text_->getText(); }

    void setTextColor(const sf::Color& color) { text_->setColor(color); }

private:
    ListItem(const ListItem& rhs) = delete;

    ListItem& operator=(const ListItem& rhs) = delete;

    Text* text_;
};

} // namespace namelessgui

#endif // NAMELESSGUI_LISTITEM_HPP
