#include "gui/ng/listwidget.hpp"

#include "gui/ng/colors.hpp"

namespace namelessgui
{

ListWidget::ListWidget()
{
	setFillColor(DEFAULT_FILL_COLOR);
	setOutlineColor(DEFAULT_OUTLINE_COLOR);
	setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);
}

ListWidget::~ListWidget()
{
}

void ListWidget::addItem(const std::string &content)
{
	Text* text = new Text();
	text->setText(content);
	items_.push_back(std::unique_ptr<Text>(text));
}

void ListWidget::render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	RectangularWidget::render(renderTarget, renderStates);

	for(auto& item : items_)
		item->render(renderTarget, renderStates);
}

} // namespace namelessgui


