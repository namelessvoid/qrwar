#ifndef NAMELESSGUI_LISTWIDGET_HPP
#define NAMELESSGUI_LISTWIDGET_HPP

#include "spritewidget.hpp"
#include "widgeteventmixin.hpp"

#include "listitem.hpp"

namespace namelessgui {

class ListWidget : public RectangularWidget, public WidgetEventMixin
{
public:
    ListWidget();

    ~ListWidget() override;

    void addItem(const std::string& content);

    void render(sf::RenderTarget&, sf::RenderStates) const override;

	bool handleEvent(const qrw::IEvent& event) override;

    bool isVisible() const override;

	void setPosition(const sf::Vector2f& position) override;

	void setSize(const sf::Vector2f& size) override;

	sf::FloatRect getWidgetArea() const override;

	Signal<const std::string&> signalItemSelected;

private:
	void slotClicked();
	void slotScrollBarValueChanged(float value)	{ scrollValue_ = value; }

	void selectItem(ListItem& item);

	sf::Vector2f computeItemPosition(int index);

	ListWidget(const ListWidget& rhs) = delete;

	ListWidget& operator=(const ListWidget& rhs) = delete;

	std::vector<std::unique_ptr<ListItem>> items_;
	ListItem* selectedItem_;

	class ScrollBar* scrollBar_;

	float scrollValue_;

	const float ITEM_HEIGHT = 30;
	const float SCROLLBAR_WIDTH = 10;
};


} // namespace namelessgui

#endif // NAMELESSGUI_LISTWIDGET_HPP
