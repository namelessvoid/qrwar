#include "gui/ng/messagedialog.hpp"

namespace namelessgui
{

MessageDialog::MessageDialog()
{
    label_ = new Label();
    label_->setText("Dummy text");
    label_->setWordWrap(true);
    addWidget(label_);

    closeButton_ = new Button();
    closeButton_->setText("Close");
    closeButton_->signalClicked.connect([this] { signalClosed.emit(); });
    closeButton_->setAnchor({0.5, 1.0});
    closeButton_->setParentAnchor({0.5, 1.0});
    closeButton_->setRelativePosition({0.0, -5.0});
    addWidget(closeButton_);

    setSize({300.0, 200.0});
}

void MessageDialog::setSize(const sf::Vector2f& size)
{
    Window::setSize(size);
    label_->setSize(size);
}

} // namespace namelessgui
