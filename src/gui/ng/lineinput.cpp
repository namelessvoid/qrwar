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

	allowedCharacters_ = "abcdefghijklmnopqrwstuvxyzABCDEFGHIJKLMNOPQRTUVWXYZ1234567890.-, ";
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
}

bool LineInput::handleEvent(const qrw::IEvent &event)
{
	if(event.getName() == qrw::AsciiInputEvent::name)
	{
		char character = static_cast<const qrw::AsciiInputEvent&>(event).character;

		if(allowedCharacters_.find(character) != std::string::npos)
		{
			std::string text = textWidget_->getText() + character;
			textWidget_->setText(text);

			return true;
		}
	}

	return Widget::handleEvent(event);
}

} // namespace namelessgui
