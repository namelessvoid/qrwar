#ifndef QRW_SPRITECOMPONENT_HPP
#define QRW_SPRITECOMPONENT_HPP

#include <SFML/System/Vector2.hpp>

#include "foundation/gamecomponent.hpp"
#include "rendering/renderable.hpp"

namespace sf
{
class RectangleShape;
class Texture;
class RenderTarget;
}

namespace qrw
{

class SpriteComponent : public GameComponent, public Renderable
{
public:
	SpriteComponent(Layer layer);

	virtual ~SpriteComponent();

	void setTexture(const sf::Texture* texture);

	void setRepeateTexture(bool repeate);

	void setSize(const sf::Vector2f& size);

	void setPosition(const sf::Vector2f& position);

	virtual void render(sf::RenderTarget& renderTarget) override;

private:
	sf::RectangleShape* _rectangle;
};

} // namespace qrw

#endif // QRW_SPRITECOMPONENT_HPP
