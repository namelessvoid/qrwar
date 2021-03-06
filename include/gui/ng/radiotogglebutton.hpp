#ifndef NAMELESSGUI_RADIOTOGGLEBUTTON_HPP
#define NAMELESSGUI_RADIOTOGGLEBUTTON_HPP value

#include "gui/ng/button.hpp"

#include <memory>

namespace namelessgui
{

// Foreward declarations
class ButtonGroup;

class RadioToggleButton : public Button
{
public:
	typedef std::shared_ptr<RadioToggleButton> SharedPtr;

	enum ERadioButtonStatus
	{
		ERBS_INACTIVE,
		ERBS_ACTIVE,
		ERBS_HOVER,
		ERBS_COUNT
	};

	RadioToggleButton(std::shared_ptr<ButtonGroup> spButtonGroup, std::string id = "");
	~RadioToggleButton();

	void deactivate();

	std::shared_ptr<ButtonGroup> getButtonGroup();

	Signal<> signalActivated;

private:
	virtual void clickedSlot() override;
	virtual void mouseEnteredSlot() override;
	virtual void mouseLeftSlot() override;

	bool _isActive;
	std::shared_ptr<ButtonGroup> _spButtonGroup;
};

} // namespace namelessgui

#endif // NAMELESSGUI_RADIOTOGGLEBUTTON_HPP
