#ifndef NAMELESSGUI_LINEINPUT_HPP
#define NAMELESSGUI_LINEINPUT_HPP

#include "spritewidget.hpp"

namespace namelessgui {

class Text;

class LineInput : public RectangularWidget
{
public:
    LineInput();

    virtual ~LineInput();

    const std::string& getText() const;

    void setText(const std::string& text);

    virtual bool handleEvent(const qrw::IEvent &event) override;

	virtual void render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;

	virtual void setPosition(const sf::Vector2f& position) override;

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
