#ifndef NAMELESSGUI_SCROLLBAR_HPP
#define NAMELESSGUI_SCROLLBAR_HPP

#include "spritewidget.hpp"

namespace namelessgui {

class ScrollBar : public RectangularWidget
{
public:
	ScrollBar();

	~ScrollBar();

	virtual void setSize(const sf::Vector2f& size) override;

	void setMaxValue(float maxValue) { maxValue_ = maxValue; }
	void setStepSize(float stepSize) { stepSize_ = stepSize; }

	Signal<float> signalValueChanged;

private:
	void stepScroll(float direction, float stepCount = 1);
	void smoothScroll(float direction, float elapsedTimeInSeconds);

	void updateScrollIndicator();

	class Button* scrollUpButton_;
	class Button* scrollDownButton_;
	RectangularWidget* scrollIndicator_;

	float currentValue_;
	float maxValue_;
	float stepSize_;

	const float UP = -1;
	const float DOWN = 1;

	ScrollBar(const ScrollBar& rhs) = delete;

	ScrollBar& operator=(const ScrollBar& rhs) = delete;
};


} // namespace namelessgui

#endif // NAMELESSGUI_SCROLLBAR_HPP
