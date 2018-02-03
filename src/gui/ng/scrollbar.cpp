#include "gui/ng/scrollbar.hpp"

#include "gui/ng/colors.hpp"

#include "gui/ng/button.hpp"

namespace namelessgui
{

ScrollBar::ScrollBar()
	: currentValue_(0),
	  maxValue_(1),
	  stepSize_(0.1)
{
	setOutlineColor(DEFAULT_OUTLINE_COLOR);
	setOutlineThickness(DEFAULT_OUTLINE_THICKNESS);

	scrollUpButton_ = new Button();
	scrollUpButton_->signalClicked.connect([this] { slotScrollUpButtonClicked(); });
	scrollUpButton_->setText("^");
	scrollUpButton_->setSize(this->getSize());
	addWidget(scrollUpButton_);

	scrollDownButton_ = new Button();
	scrollDownButton_->signalClicked.connect([this] { slotScrollDownButtonClicked(); });
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

void ScrollBar::slotScrollUpButtonClicked()
{
	currentValue_ -= stepSize_;
	currentValue_ = std::max(0.0f, currentValue_);
	signalValueChanged.emit(currentValue_);
}

void ScrollBar::slotScrollDownButtonClicked()
{
	currentValue_ += stepSize_;
	currentValue_ = std::min(maxValue_, currentValue_);
	signalValueChanged.emit(currentValue_);
}

} // namespace namelessgui
