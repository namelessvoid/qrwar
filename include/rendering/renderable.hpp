#ifndef QRW_RENDERABLE_HPP
#define QRW_RENDERABLE_HPP

namespace sf
{
class RenderTarget;
}

namespace qrw
{

class Renderable
{
public:
	virtual void render(sf::RenderTarget& renderTarget) = 0;
};

} // namespace qrw

#endif // QRW_RENDERABLE_HPP
