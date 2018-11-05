#ifndef NAMELESSGUI_MESSAGEDIALOG_HPP
#define NAMELESSGUI_MESSAGEDIALOG_HPP

#include "gui/ng/window.hpp"
#include "gui/ng/label.hpp"
#include "gui/ng/button.hpp"

namespace namelessgui {

class MessageDialog : public Window
{
public:
	MessageDialog();

	~MessageDialog() override = default;

	void setSize(const sf::Vector2f& size) override;

	inline void setMessage(const std::string& message) { label_->setText(message); }
	inline void setButtonText(const std::string& text) { closeButton_->setText(text); }

	Signal<> signalClosed;

private:
	MessageDialog(const MessageDialog& rhs) = delete;

	MessageDialog& operator=(const MessageDialog& rhs) = delete;

	Label* label_;
	Button* closeButton_;
};


} // namespace namelessgui

#endif // NAMELESSGUI_MESSAGEDIALOG_HPP
