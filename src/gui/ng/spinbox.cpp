#include "gui/ng/spinbox.hpp"

#include <limits>

#include "gui/ng/colors.hpp"
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
	incrementButton_->signalClicked.connect(std::bind(&SpinBox::incrementValue, this));
	addWidget(incrementButton_);

	decrementButton_ = new Button();
	decrementButton_->setText("-");
	decrementButton_->setAnchor({1, 1});
	decrementButton_->setParentAnchor({1, 1});
	decrementButton_->signalClicked.connect(std::bind(&SpinBox::decrementValue, this));
	addWidget(decrementButton_);

	lineInput_ = new LineInput();
	lineInput_->setAllowedCharacters("1234567890");
	lineInput_->setText(std::to_string(value_));
	lineInput_->signalEdited.connect([this]() { validateLineInput(); });
	lineInput_->signalDoneEditing.connect([this]() { setValueFromLineInput(); });
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
	// clamp to range
	value_ = std::min(std::max(value, minValue_), maxValue_);

	lineInput_->setOutlineColor(DEFAULT_OUTLINE_COLOR);
	lineInput_->setText(std::to_string(value_));

	signalChanged.emit(value_);
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
	value_ < maxValue_ ? setValue(value_ + 1) : setValue(maxValue_);
}

void SpinBox::decrementValue()
{
	value_ > minValue_ ? setValue(value_ - 1) : setValue(minValue_);
}

void SpinBox::validateLineInput()
{
	try
	{
		unsigned int newValue = std::stoi(lineInput_->getText());

		if(newValue == value_)
			return;

		if(newValue < minValue_ || newValue > maxValue_)
			lineInput_->setOutlineColor(ERROR_OUTLINE_COLOR);
		else
			lineInput_->setOutlineColor(DEFAULT_OUTLINE_COLOR);
	}
	catch(std::invalid_argument)
	{
		lineInput_->setOutlineColor(ERROR_OUTLINE_COLOR);
	}
}

void SpinBox::setValueFromLineInput()
{
	try
	{
		unsigned int newValue = std::stoi(lineInput_->getText());

		if(newValue == value_)
			return;

		if(newValue < minValue_)
			newValue = minValue_;
		else if(newValue > maxValue_)
			newValue = maxValue_;

		value_ = newValue;
		lineInput_->setText(std::to_string(value_));

		signalChanged.emit(value_);
	}
	catch(std::invalid_argument)
	{
		lineInput_->setText(std::to_string(minValue_));
	}

	lineInput_->setOutlineColor(DEFAULT_OUTLINE_COLOR);
}

} // namespace namelessgui
