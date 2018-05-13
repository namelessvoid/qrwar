#include "gui/ng/lineinput.hpp"

#include "gui/ng/colors.hpp"
#include "gui/ng/text.hpp"
#include "gui/ng/croppingviewfactory.hpp"

#include "eventsystem/inputevents.hpp"

namespace namelessgui
{

LineInput::LineInput()
{
	textWidget_ = new Text();
	textWidget_->setText("DUMMY TEXT");
	addWidget(textWidget_);

	cursor_ = new RectangleShape();
	cursor_->setFillColor(LINE_INPUT_CURSOR_COLOR);
	cursor_->setSize({5, 20});
	updateCursorPosition();

	allowedCharacters_ = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.-, ";

	signalKeyboardFocusLost.connect([this] { signalDoneEditing.emit(); });

	setFillColor(sf::Color(60, 60, 60, 255));
	setOutlineThickness(1);
	setOutlineColor(sf::Color(120, 120, 120));
}

LineInput::~LineInput()
{
	delete cursor_;
}

const std::string& LineInput::getText() const
{
	return textWidget_->getText();
}

void LineInput::setText(const std::string& text)
{
	textWidget_->setText(text);
	updateCursorPosition();
	signalEdited.emit();
}

bool LineInput::isVisible() const
{
	return RectangularWidget::isVisible();
}

bool LineInput::handleEvent(const qrw::IEvent &event)
{
	if(hasKeyboardFocus())
	{
		if(event.getName() == qrw::AsciiInputEvent::name)
		{
			char character = static_cast<const qrw::AsciiInputEvent&>(event).character;

			if(allowedCharacters_.find(character) != std::string::npos)
			{
				std::string text = textWidget_->getText() + character;
				setText(text);
				return true;
			}
		}
		else if(event.getName() == qrw::KeyPressedEvent::name)
		{
			qrw::KeyboardKey key = static_cast<const qrw::KeyPressedEvent&>(event).key;
			if(key == qrw::KeyboardKey::Backspace)
			{
				std::string text = textWidget_->getText();
				setText(text.substr(0, text.size() -1));
			}
			else if(key == qrw::KeyboardKey::Return || key == qrw::KeyboardKey::Esc)
			{
				signalDoneEditing.emit();
				setKeyboardFocus(false);
			}
			return true;
		}
	} // if(hasKeyboardFocus)

	return WidgetEventMixin::handleEvent(event);
}

void LineInput::render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	if(!isVisible())
		return;

	renderTarget.draw(*static_cast<const RectangleShape*>(this), renderStates);

	sf::View prevView = renderTarget.getView();

	CroppingViewFactory croppingViewFactory;
	sf::View lineInputView = croppingViewFactory.createView(renderTarget, getPosition(), getSize());

	if(!textFitsIntoWidget())
	{
		// Apply text scrolling
		float xOffset = textWidget_->getSize().x - (getSize().x - cursor_->getSize().x);
		lineInputView.move({xOffset, 0});
	}

	renderTarget.setView(lineInputView);

	textWidget_->render(renderTarget, renderStates);

	renderTarget.setView(prevView);

	if(hasKeyboardFocus())
	{
		renderTarget.draw(*cursor_, renderStates);
	}
}

void LineInput::setPosition(const sf::Vector2f& position)
{
	RectangularWidget::setPosition(position);
	updateCursorPosition();
}

void LineInput::updateCursorPosition()
{
	const sf::Vector2f& textSize = textWidget_->getSize();

	const float cursorYPosition = getPosition().y + 0.5f * getSize().y - 0.5 * cursor_->getSize().y;

	if(textFitsIntoWidget())
		cursor_->setPosition({getPosition().x + textSize.x + 2, cursorYPosition});
	else
		cursor_->setPosition({getPosition().x + getSize().x - cursor_->getSize().x, cursorYPosition});
}

bool LineInput::textFitsIntoWidget() const
{
	return textWidget_->getSize().x < (getSize().x - cursor_->getSize().x);
}

} // namespace namelessgui
