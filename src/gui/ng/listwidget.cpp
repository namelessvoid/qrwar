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
	Text* text = new Text();
	text->setText(content);
	text->setPosition({0, ITEM_HEIGHT * items_.size()});
	items_.push_back(std::unique_ptr<Text>(text));

	// If this is the first item, select it
	if(items_.size() == 1)
		selectItem(*text);
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
	items_.at(0)->setColor(sf::Color::Red);
	std::cout << qrw::Mouse::getPosition().x << "/" << qrw::Mouse::getPosition().y << std::endl << std::flush;

	for(auto& item : items_)
	{
		sf::Vector2i mousePosition = qrw::Mouse::getPosition();
		if(item->getWidgetArea().contains(mousePosition.x, mousePosition.y))
			selectItem(*item);
		else
			item->setColor(sf::Color::White);
	}
}

void ListWidget::selectItem(Text& item)
{
	selectedItem_ = &item;
	selectedItem_->setColor(sf::Color::Red);
	signalItemSelected.emit(selectedItem_->getText());
}

} // namespace namelessgui


