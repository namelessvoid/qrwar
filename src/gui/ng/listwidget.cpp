#include "gui/ng/listwidget.hpp"

#include "gui/ng/colors.hpp"
#include "gui/ng/scrollbar.hpp"
#include "gui/ng/croppingviewfactory.hpp"

#include "core/mouse.hpp"

#include <iostream>

namespace namelessgui
{

ListWidget::ListWidget()
{
	setFillColor(DEFAULT_FILL_COLOR);
	setOutlineColor(DEFAULT_OUTLINE_COLOR);
	setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);

	ScrollBar* scrollBar = new ScrollBar();
	scrollBar->setSize({SCROLLBAR_WIDTH, this->getSize().y});
	scrollBar->setParentAnchor({1, 0});
	scrollBar->setAnchor({1, 0});
	addWidget(scrollBar);

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
	item->setSize({this->getSize().x - SCROLLBAR_WIDTH, ITEM_HEIGHT});
	items_.push_back(std::unique_ptr<ListItem>(item));

	// If this is the first item, select it
	if(items_.size() == 1)
		selectItem(*item);
}

void ListWidget::render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	RectangularWidget::render(renderTarget, renderStates);

	// Render list items with cropping view
	sf::View prevView = renderTarget.getView();

	CroppingViewFactory croppingViewFactory;
	sf::Vector2f viewportSize = getSize() - sf::Vector2f(SCROLLBAR_WIDTH, 0);
	sf::View listItemView = croppingViewFactory.createView(renderTarget, getPosition(), viewportSize);

	renderTarget.setView(listItemView);

	for(auto& item : items_)
		item->render(renderTarget, renderStates);

	renderTarget.setView(prevView);
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


