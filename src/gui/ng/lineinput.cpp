#include "gui/ng/lineinput.hpp"

#include "gui/ng/text.hpp"

#include "eventsystem/inputevents.hpp"

namespace namelessgui
{

LineInput::LineInput()
{
	textWidget_ = new Text();
	textWidget_->setText("DUMMY TEXT");
	addWidget(textWidget_);

	cursor_ = new RectangleShape();
	cursor_->setFillColor(sf::Color::Red);
	cursor_->setSize({5, 20});
	updateCursorPosition();

	allowedCharacters_ = "abcdefghijklmnopqrwstuvxyzABCDEFGHIJKLMNOPQRTUVWXYZ1234567890.-, ";

	setFillColor(sf::Color(60, 60, 60, 255));
	setOutlineThickness(1);
	setOutlineColor(sf::Color(120, 120, 120));
}

LineInput::~LineInput()
{
}

const std::string& LineInput::getText() const
{
	return textWidget_->getText();
}

void LineInput::setText(const std::string &text)
{
	textWidget_->setText(text);
	updateCursorPosition();
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
				textWidget_->setText(text);
				updateCursorPosition();

				return true;
			}
		}
		else if(event.getName() == qrw::KeyPressedEvent::name)
		{
			qrw::KeyPressedEvent::Key key = static_cast<const qrw::KeyPressedEvent&>(event).key;
			if(key == qrw::KeyPressedEvent::Key::Backspace)
			{
				std::string text = textWidget_->getText();
				textWidget_->setText(text.substr(0, text.size() -1));
				updateCursorPosition();

				return true;
			}
		}
	} // if(hasKeyboardFocus)

	return Widget::handleEvent(event);
}

void LineInput::render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const
{
	if(!isVisible())
		return;

	renderTarget.draw(*static_cast<const RectangleShape*>(this), renderStates);

	sf::View prevView = renderTarget.getView();

	sf::View lineInputView({getPosition().x, getPosition().y, getSize().x, getSize().y});

	sf::FloatRect inputLineViewport({
										getPosition().x / renderTarget.getSize().x,
										getPosition().y / renderTarget.getSize().y,
										getSize().x / renderTarget.getSize().x,
										getSize().y / renderTarget.getSize().y
									});

	lineInputView.setViewport(inputLineViewport);
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

	cursor_->setPosition({getPosition().x + textSize.x + 2, getPosition().y + 0.5f * cursor_->getSize().y});
}

} // namespace namelessgui
