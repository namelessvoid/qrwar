#include "gui/ng/spinbox.hpp"

#include <limits>

#include "gui/ng/button.hpp"
#include "gui/ng/lineinput.hpp"

namespace namelessgui
{

SpinBox::SpinBox()
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
	addWidget(lineInput_);

	resizeButtons();
	setValue(10);
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
	value_ = value;
	lineInput_->setText(std::to_string(value));
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
	if(value_ == std::numeric_limits<unsigned int>::max())
		return;

	setValue(value_ + 1);
}

void SpinBox::decrementValue()
{
	if(value_ == std::numeric_limits<unsigned int>::min())
		return;

	setValue(value_ - 1);
}

} // namespace namelessgui
