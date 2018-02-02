#ifndef NAMELESSGUI_LISTWIDGET_HPP
#define NAMELESSGUI_LISTWIDGET_HPP

#include "spritewidget.hpp"
#include "text.hpp"

namespace namelessgui {

class ListWidget : public RectangularWidget
{
public:
    ListWidget();

    ~ListWidget();

    void addItem(const std::string& content);

    virtual void render(sf::RenderTarget&, sf::RenderStates) const override;

private:
    ListWidget(const ListWidget& rhs) = delete;

    ListWidget& operator=(const ListWidget& rhs) = delete;

    std::vector<std::unique_ptr<Text>> items_;
};


} // namespace namelessgui

#endif // NAMELESSGUI_LISTWIDGET_HPP
