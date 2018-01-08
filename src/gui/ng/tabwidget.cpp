#include "gui/ng/tabwidget.hpp"

#include <cassert>

#include "gui/ng/buttongroup.hpp"
#include "gui/ng/radiotogglebutton.hpp"

namespace namelessgui
{

TabWidget::TabWidget()
	: buttonSize_(20, 20)
{
	setSize({100, 100});
	buttonGroup_ = std::make_shared<ButtonGroup>();
}

TabWidget::~TabWidget()
{
}

void TabWidget::addTab(const sf::Texture* buttonImage, Widget* widget)
{
	assert(widget != nullptr);

	size_t index = buttons_.size();

	RadioToggleButton* button = new RadioToggleButton(buttonGroup_);
	button->setImage(buttonImage);
	button->setSize(buttonSize_);
	button->setRelativePosition(getButtonRelativePosition(index));
	button->signalActivated.connect(std::bind(&TabWidget::setActiveTab, this, index));
	addWidget(button);
	buttons_.push_back(button);

	widget->setAnchor({0, 0});
	widget->setParentAnchor({0, 0});
	widget->setSize({getSize().x, getSize().y - buttonSize_.y - 5});
	widget->setRelativePosition({0, buttonSize_.y + 5 });
	addWidget(widget);
	widgets_.push_back(widget);
	widget->setVisible(false);

	// If this is the first tab, make it active by default
	if(index == 0)
	{
		button->signalClicked.emit();
		widget->setVisible(true);
	}
}

void TabWidget::setButtonSize(const sf::Vector2f& buttonSize)
{
	buttonSize_ = buttonSize;

	for(size_t i = 0; i < buttons_.size(); ++i)
	{
		Button* button = buttons_.at(i);
		button->setSize(buttonSize);
		button->setRelativePosition(getButtonRelativePosition(i));
	}
}

void TabWidget::setActiveTab(size_t index)
{
	bool tabVisible = false;
	for(size_t i = 0; i < widgets_.size(); ++i)
	{
		tabVisible = i == index;
		widgets_.at(i)->setVisible(tabVisible);
	}
}

sf::FloatRect TabWidget::getWidgetArea()
{
	return sf::FloatRect(getPosition(), getSize());
}

void TabWidget::setSize(const sf::Vector2f &size)
{
	size_ = size;
}

sf::Vector2f TabWidget::getSize() const
{
	return size_;
}

sf::Vector2f TabWidget::getPosition() const
{
	return position_;
}

void TabWidget::setPosition(const sf::Vector2f &position)
{
	position_ = position;
}

sf::Vector2f TabWidget::getButtonRelativePosition(int index)
{
	return { index * buttonSize_.x, 0 };
}

} // namespace namelessgui
