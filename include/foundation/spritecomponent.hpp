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
	explicit SpriteComponent(GameObject& owner, Layer layer);

	~SpriteComponent() override;

	void setTexture(const sf::Texture* texture);

	void setSize(const sf::Vector2f& size);

	const sf::Vector2f& getSize();

	void setPosition(const sf::Vector2f& position) override;

	const sf::Vector2f& getPosition() const override;

	const sf::Transform& getInverseTransform() const
	{
		return _rectangle->getInverseTransform();
	}

	void setScale(sf::Vector2f scale)
	{
		_rectangle->setScale(scale);
	}

	void setOrigin(float x, float y)
	{
		_rectangle->setOrigin(x, y);
	}

	const sf::Texture* getTexture() const
	{
		return _rectangle->getTexture();
	}

	const sf::IntRect& getTextureRect() const
	{
		return _rectangle->getTextureRect();
	}

	void setFillColor(const sf::Color& color);

	virtual void render(sf::RenderTarget& renderTarget) override;

	sf::FloatRect getGlobalBounds() const;

	void enablePhysics();
	void disablePhysics();

protected:
	sf::RectangleShape* _rectangle;

	bool physicsEnabled_;
};

} // namespace qrw

#endif // QRW_SPRITECOMPONENT_HPP
