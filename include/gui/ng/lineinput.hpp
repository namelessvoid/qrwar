#ifndef NAMELESSGUI_LINEINPUT_HPP
#define NAMELESSGUI_LINEINPUT_HPP

#include "spritewidget.hpp"

namespace namelessgui {

class Text;

class LineInput : public RectangularWidget, public WidgetEventMixin
{
public:
    LineInput();

    virtual ~LineInput();

    const std::string& getText() const;

    void setText(const std::string& text);

	void setAllowedCharacters(const std::string& characters) { allowedCharacters_ = characters; }

	virtual bool isVisible() const override;

    virtual bool handleEvent(const qrw::IEvent &event) override;

	virtual void render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;

	virtual void setPosition(const sf::Vector2f& position) override;

	virtual sf::FloatRect getWidgetArea() const override { return RectangularWidget::getWidgetArea(); }

	Signal<> signalEdited;

	Signal<> signalDoneEditing;

private:
    LineInput(const LineInput& rhs) = delete;

    LineInput& operator=(const LineInput& rhs) = delete;

	void updateCursorPosition();

	bool textFitsIntoWidget() const;

    Text* textWidget_;

	RectangleShape* cursor_;

    std::string allowedCharacters_;
};


} // namespace namelessgui

#endif // NAMELESSGUI_LINEINPUT_HPP
