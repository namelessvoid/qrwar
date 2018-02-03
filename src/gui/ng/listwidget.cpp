#include "gui/ng/listwidget.hpp"

#include "gui/ng/colors.hpp"

#include "core/mouse.hpp"

#include <iostream>

namespace namelessgui
{

ListWidget::ListWidget()
{
	setFillColor(DEFAULT_FILL_COLOR);
	setOutlineColor(DEFAULT_OUTLINE_COLOR);
	setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);

	signalClicked.connect([this] { slotClicked(); });
}

ListWidget::~ListWidget()
{
}

void ListWidget::addItem(const std::string &content)
{
	ListItem* item = new ListItem();
	item->setText(content);
	item->setRelativePosition({0, ITEM_HEIGHT * items_.size()});
	item->setSize({this->getSize().x, ITEM_HEIGHT});
	items_.push_back(std::unique_ptr<ListItem>(item));

	// If this is the first item, select it
	if(items_.size() == 1)
		selectItem(*item);
}

void ListWidget::render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	RectangularWidget::render(renderTarget, renderStates);

	for(auto& item : items_)
		item->render(renderTarget, renderStates);
}

bool ListWidget::isVisible() const
{
	return RectangularWidget::isVisible();
}

sf::FloatRect ListWidget::getWidgetArea() const
{
	return RectangularWidget::getWidgetArea();
}

void ListWidget::slotClicked()
{
	for(auto& item : items_)
	{
		sf::Vector2i mousePosition = qrw::Mouse::getPosition();
		if(item->getWidgetArea().contains(mousePosition.x, mousePosition.y))
			selectItem(*item);
	}
}

void ListWidget::selectItem(ListItem& item)
{
	// Deselect currently selected item if necessary
	if(selectedItem_ != nullptr)
		selectedItem_->setTextColor(DEFAULT_TEXT_COLOR);

	selectedItem_ = &item;
	selectedItem_->setTextColor(ACTIVE_TEXT_COLOR);
	signalItemSelected.emit(selectedItem_->getText());
}

} // namespace namelessgui


