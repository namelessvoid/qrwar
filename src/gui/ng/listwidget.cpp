#include "gui/ng/listwidget.hpp"

#include "gui/ng/colors.hpp"
#include "gui/ng/scrollbar.hpp"
#include "gui/ng/croppingviewfactory.hpp"

#include "core/mouse.hpp"

#include <iostream>

namespace namelessgui
{

ListWidget::ListWidget()
	: selectedItem_(nullptr),
	  scrollValue_(0)
{
	setFillColor(DEFAULT_FILL_COLOR);
	setOutlineColor(DEFAULT_OUTLINE_COLOR);
	setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);

	scrollBar_ = new ScrollBar();
	scrollBar_->signalValueChanged.connect([this] (float value) { slotScrollBarValueChanged(value); });
	scrollBar_->setSize({SCROLLBAR_WIDTH, this->getSize().y});
	scrollBar_->setParentAnchor({1, 0});
	scrollBar_->setAnchor({1, 0});
	addWidget(scrollBar_);

	signalClicked.connect([this] { slotClicked(); });
}

ListWidget::~ListWidget()
{
}

void ListWidget::addItem(const std::string &content)
{
	ListItem* item = new ListItem();
	item->setText(content);
	item->setRelativePosition(computeItemPosition(items_.size()));
	item->setSize({this->getSize().x - SCROLLBAR_WIDTH, ITEM_HEIGHT});
	items_.push_back(std::unique_ptr<ListItem>(item));

	// If this is the first item, select it
	if(items_.size() == 1)
		selectItem(*item);

	//scrollBar_->setMaxValue(items_.size() * ITEM_HEIGHT - getSize().y);
}

void ListWidget::render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	RectangularWidget::render(renderTarget, renderStates);

	// Render list items with cropping view
	sf::View prevView = renderTarget.getView();

	CroppingViewFactory croppingViewFactory;
	sf::Vector2f viewportSize = getSize() - sf::Vector2f(SCROLLBAR_WIDTH, 0);
	sf::View listItemView = croppingViewFactory.createView(renderTarget, getPosition(), viewportSize);
	listItemView.move(0, scrollValue_ * items_.size() * ITEM_HEIGHT);

	renderTarget.setView(listItemView);

	for(auto& item : items_)
		item->render(renderTarget, renderStates);

	renderTarget.setView(prevView);
}

bool ListWidget::isVisible() const
{
	return RectangularWidget::isVisible();
}

void ListWidget::setPosition(const sf::Vector2f& position)
{
	RectangularWidget::setPosition(position);

	for(size_t i = 0; i < items_.size(); ++i)
		items_.at(i)->setPosition(computeItemPosition(i));
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
		mousePosition.y += scrollValue_;
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

sf::Vector2f ListWidget::computeItemPosition(int index)
{
	return {getPosition().x, getPosition().y + index * ITEM_HEIGHT};
}

} // namespace namelessgui


