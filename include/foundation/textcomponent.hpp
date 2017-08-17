#ifndef QRW_TEXTCOMPONENT_HPP
#define QRW_TEXTCOMPONENT_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

#include "foundation/gamecomponent.hpp"
#include "rendering/renderable.hpp"
#include "rendering/rendersystem.hpp"

namespace qrw
{

class TextComponent : public GameComponent, public Renderable
{
public:
    TextComponent(Layer layer);

    void setText(const std::string& text);

    virtual void render(sf::RenderTarget &renderTarget) override;
    virtual void setPosition(const sf::Vector2f &position) override;
    virtual const sf::Vector2f &getPosition() const override;

private:
    sf::Font m_font;
    sf::Text m_text;
};

} // namespace qrw

#endif // QRW_TEXTCOMPONENT_HPP
