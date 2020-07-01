#ifndef QRW_RENDERABLE_HPP
#define QRW_RENDERABLE_HPP

#include <SFML/System/Vector2.hpp>

namespace sf
{
class RenderTarget;
}

namespace qrw
{

typedef unsigned int Layer;

class Renderable
{
public:
	explicit Renderable(Layer layer);

	virtual ~Renderable();

	virtual void render(sf::RenderTarget& renderTarget) = 0;

	Layer getLayer();

	inline bool isVisible() const { return visible_; }
	void setVisible(bool visible) { visible_ = visible; }

	virtual void setPosition(const sf::Vector2f& position) = 0;
	virtual const sf::Vector2f& getPosition() const = 0;

	void setZIndex(float zIndex) { zIndex_ = zIndex; }
	float getZIndex() const { return zIndex_; }

private:
	Layer layer_;
	float zIndex_;
	bool visible_;
};

} // namespace qrw

#endif // QRW_RENDERABLE_HPP
