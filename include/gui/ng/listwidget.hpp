#ifndef NAMELESSGUI_LISTWIDGET_HPP
#define NAMELESSGUI_LISTWIDGET_HPP

#include "spritewidget.hpp"
#include "text.hpp"
#include "widgeteventmixin.hpp"

namespace namelessgui {

class ListWidget : public RectangularWidget, public WidgetEventMixin
{
public:
    ListWidget();

    ~ListWidget();

    void addItem(const std::string& content);

    virtual void render(sf::RenderTarget&, sf::RenderStates) const override;

    virtual bool isVisible() const override;

    virtual sf::FloatRect getWidgetArea() const override;

private:
    void slotClicked();

    ListWidget(const ListWidget& rhs) = delete;

    ListWidget& operator=(const ListWidget& rhs) = delete;

    std::vector<std::unique_ptr<Text>> items_;

    const float ITEM_HEIGHT = 30;
};


} // namespace namelessgui

#endif // NAMELESSGUI_LISTWIDGET_HPP
