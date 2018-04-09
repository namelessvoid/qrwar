#include <SFML/Graphics/RectangleShape.hpp>

#include "gui/ng/radiotogglebutton.hpp"

#include <cassert>

#include "gui/ng/buttongroup.hpp"

namespace namelessgui
{

RadioToggleButton::RadioToggleButton(std::shared_ptr<ButtonGroup> spButtonGroup, std::string id)
	: Button(id),
	  _isActive(false)
{
	assert(spButtonGroup != nullptr);

	_spButtonGroup = spButtonGroup;
	_spButtonGroup->addButton(this);
}

RadioToggleButton::~RadioToggleButton()
{
}

void RadioToggleButton::deactivate()
{
	_isActive = false;
	setFillColor(sf::Color(60, 60, 60, 255));
}

std::shared_ptr<ButtonGroup> RadioToggleButton::getButtonGroup()
{
	return _spButtonGroup;
}

void RadioToggleButton::clickedSlot()
{
	_isActive = true;
	signalActivated.emit();
}

void RadioToggleButton::mouseEnteredSlot()
{
	if(!_isActive)
		Button::mouseEnteredSlot();
}

void RadioToggleButton::mouseLeftSlot()
{
	if(!_isActive)
		Button::mouseLeftSlot();
}

} // namespace namelessgui
