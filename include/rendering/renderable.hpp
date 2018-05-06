#ifndef QRW_RENDERABLE_HPP
#define QRW_RENDERABLE_HPP

#include <SFML/System/Vector2.hpp>

namespace sf
{
class RenderTarget;
}

namespace qrw
{

typedef int Layer;

class Renderable
{
public:
	Renderable(Layer layer);

	virtual ~Renderable();

	virtual void render(sf::RenderTarget& renderTarget) = 0;

	Layer getLayer();

	inline bool isVisible() const { return m_visible; }
	void setVisible(bool visible) { m_visible = visible; }

	virtual void setPosition(const sf::Vector2f& position) = 0;
	virtual const sf::Vector2f& getPosition() const = 0;

private:
	unsigned char m_layer;

	bool m_visible;
};

} // namespace qrw

#endif // QRW_RENDERABLE_HPP
