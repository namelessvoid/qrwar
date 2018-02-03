#include "gui/ng/scrollbar.hpp"

#include "gui/ng/colors.hpp"

#include "gui/ng/button.hpp"

namespace namelessgui
{

ScrollBar::ScrollBar()
{
	setOutlineColor(DEFAULT_OUTLINE_COLOR);
	setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);

	scrollUpButton_ = new Button();
	scrollUpButton_->setText("^");
	scrollUpButton_->setSize(this->getSize());
	addWidget(scrollUpButton_);

	scrollDownButton_ = new Button();
	scrollDownButton_->setText("v");
	scrollDownButton_->setSize(this->getSize());
	scrollDownButton_->setAnchor({0, 1});
	scrollDownButton_->setParentAnchor({0, 1});
	addWidget(scrollDownButton_);
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::setSize(const sf::Vector2f& size)
{
	RectangularWidget::setSize(size);

	sf::Vector2f buttonSize(size.x, size.x);
	scrollUpButton_->setSize(buttonSize);
	scrollUpButton_->setFontSize(buttonSize.x);
	scrollDownButton_->setSize(buttonSize);
	scrollDownButton_->setFontSize(buttonSize.x);
}

} // namespace namelessgui
