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
	scrollUpButton_->signalClicked.connect([this] { stepScroll(UP); });
	scrollUpButton_->signalLeftMouseButtonHeld.connect([this] (float frameTimeInSeconds) { smoothScroll(UP, frameTimeInSeconds); });
//	scrollUpButton_->setText("^");
	scrollUpButton_->setSize(this->getSize());
	scrollUpButton_->setOutlineThickness(1);
	scrollUpButton_->setOutlineColor(DEFAULT_OUTLINE_COLOR);
	addWidget(scrollUpButton_);

	scrollDownButton_ = new Button();
	scrollDownButton_->signalClicked.connect([this] { stepScroll(DOWN); });
	scrollDownButton_->signalLeftMouseButtonHeld.connect([this] (float frameTimeInSeconds) { smoothScroll(DOWN, frameTimeInSeconds); });
//	scrollDownButton_->setText("v");
	scrollDownButton_->setSize(this->getSize());
	scrollDownButton_->setOutlineThickness(1);
	scrollDownButton_->setOutlineColor(DEFAULT_OUTLINE_COLOR);
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

void ScrollBar::stepScroll(float direction, float stepCount)
{
	currentValue_ += direction * stepCount * stepSize_;
	currentValue_ = std::max(0.0f, currentValue_);
	signalValueChanged.emit(currentValue_);
}

void ScrollBar::smoothScroll(float direction, float elapsedTimeInSeconds)
{
	stepScroll(direction, elapsedTimeInSeconds * 10);
}

} // namespace namelessgui
