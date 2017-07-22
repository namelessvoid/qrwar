#ifndef QRW_SPRITECOMPONENT_HPP
#define QRW_SPRITECOMPONENT_HPP

#include "foundation/gamecomponent.hpp"

#include <SFML/System/Vector2.hpp>

namespace sf
{
class RectangleShape;
class Texture;
class RenderTarget;
}

namespace qrw
{

class SpriteComponent : public GameComponent
{
public:
	SpriteComponent();

	virtual ~SpriteComponent();

	void setTexture(const sf::Texture* texture);

	void setSize(const sf::Vector2f& size);

	void setPosition(const sf::Vector2f& position);

	void render(sf::RenderTarget* renderTarget);

private:
	sf::RectangleShape* _rectangle;
};

} // namespace qrw

#endif // QRW_SPRITECOMPONENT_HPP
