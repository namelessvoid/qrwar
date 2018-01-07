#ifndef NAMELESSGUI_SPINBOX_HPP
#define NAMELESSGUI_SPINBOX_HPP

#include "spritewidget.hpp"

namespace namelessgui {

class Button;
class LineInput;

class SpinBox : public RectangularWidget
{
public:
    SpinBox();

    ~SpinBox();

    void setSize(const sf::Vector2f& size) override;

	void setValue(unsigned int value);

	void setMinValue(unsigned int minValue);

	void setMaxValue(unsigned int maxValue);

private:
    SpinBox(const SpinBox& rhs) = delete;

    SpinBox& operator=(const SpinBox& rhs) = delete;

    void resizeButtons();

	void incrementValue();

	void decrementValue();

	unsigned int value_;
	unsigned int minValue_;
	unsigned int maxValue_;

    Button* incrementButton_;
    Button* decrementButton_;
	LineInput* lineInput_;
};


} // namespace namelessgui

#endif // NAMELESSGUI_SPINBOX_HPP
