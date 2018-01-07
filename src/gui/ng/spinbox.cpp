#include "gui/ng/spinbox.hpp"

#include <limits>

#include "gui/ng/button.hpp"
#include "gui/ng/lineinput.hpp"

namespace namelessgui
{

SpinBox::SpinBox()
	: value_(std::numeric_limits<unsigned int>::min()),
	  minValue_(std::numeric_limits<unsigned int>::min()),
	  maxValue_(std::numeric_limits<unsigned int>::max())
{
	incrementButton_ = new Button();
	incrementButton_->setText("+");
	incrementButton_->setAnchor({1, 0});
	incrementButton_->setParentAnchor({1, 0});
	incrementButton_->signalclicked.connect(std::bind(&SpinBox::incrementValue, this));
	addWidget(incrementButton_);

	decrementButton_ = new Button();
	decrementButton_->setText("-");
	decrementButton_->setAnchor({1, 1});
	decrementButton_->setParentAnchor({1, 1});
	decrementButton_->signalclicked.connect(std::bind(&SpinBox::decrementValue, this));
	addWidget(decrementButton_);

	lineInput_ = new LineInput();
	lineInput_->setAllowedCharacters("1234567890");
	addWidget(lineInput_);

	resizeButtons();
}

SpinBox::~SpinBox()
{
}

void SpinBox::setSize(const sf::Vector2f &size)
{
	RectangularWidget::setSize(size);
	resizeButtons();
}

void SpinBox::setValue(unsigned int value)
{
	value_ = std::min(std::max(value, minValue_), maxValue_);

	lineInput_->setText(std::to_string(value_));
}

void SpinBox::setMinValue(unsigned int minValue)
{
	minValue_ = minValue;
	setValue(value_);
}

void SpinBox::setMaxValue(unsigned int maxValue)
{
	maxValue_ = maxValue;
	setValue(value_);
}

void SpinBox::resizeButtons()
{
	float buttonSize = 0.5f * getSize().y;
	incrementButton_->setSize({buttonSize, buttonSize});
	decrementButton_->setSize({buttonSize, buttonSize});
	incrementButton_->setFontSize(buttonSize * 0.5f);
	decrementButton_->setFontSize(buttonSize);

	lineInput_->setSize({getSize().x - buttonSize, getSize().y});
}

void SpinBox::incrementValue()
{
	if(value_ == maxValue_)
		return;

	setValue(value_ + 1);
}

void SpinBox::decrementValue()
{
	if(value_ == minValue_)
		return;

	setValue(value_ - 1);
}

} // namespace namelessgui
