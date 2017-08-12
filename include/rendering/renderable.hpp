#ifndef QRW_RENDERABLE_HPP
#define QRW_RENDERABLE_HPP

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

private:
	unsigned char m_layer;
};

} // namespace qrw

#endif // QRW_RENDERABLE_HPP
