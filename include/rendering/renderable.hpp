#ifndef QRW_RENDERABLE_HPP
#define QRW_RENDERABLE_HPP

#include <SFML/System/Vector2.hpp>

namespace sf
{
class RenderTarget;
}

namespace qrw
{

typedef unsigned char Layer;

class Renderable
{
public:
	Renderable(Layer layer)
		: m_layer(layer)
	{}

	virtual void render(sf::RenderTarget& renderTarget) = 0;

	inline Layer getLayer() { return m_layer; }

	virtual void setPosition(const sf::Vector2f& position) = 0;
	virtual const sf::Vector2f& getPosition() const = 0;

private:
	unsigned char m_layer;
};

} // namespace qrw

#endif // QRW_RENDERABLE_HPP
