#ifndef QRW_SPRITECOMPONENT_HPP
#define QRW_SPRITECOMPONENT_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "foundation/gamecomponent.hpp"
#include "rendering/renderable.hpp"

namespace sf
{
class RectangleShape;
class Texture;
class RenderTarget;
class Color;
}

namespace qrw
{

class SpriteComponent : public GameComponent, public Renderable
{
public:
	SpriteComponent(Layer layer);

	virtual ~SpriteComponent();

	void setTexture(const sf::Texture* texture);

	void setRepeateTexture(bool repeate, float scale = 1);

	void setSize(const sf::Vector2f& size);

	const sf::Vector2f& getSize();

	void setPosition(const sf::Vector2f& position) override;

	const sf::Vector2f& getPosition() const override;

	void setRotation(const float degrees)
	{
		_rectangle->setRotation(degrees);
	}

	void setOrigin(float x, float y)
	{
		_rectangle->setOrigin(x, y);
	}

	sf::Vector2f getCenter();

	void setFillColor(const sf::Color& color);

	virtual void render(sf::RenderTarget& renderTarget) override;

protected:
	sf::RectangleShape* _rectangle;
};

} // namespace qrw

#endif // QRW_SPRITECOMPONENT_HPP
