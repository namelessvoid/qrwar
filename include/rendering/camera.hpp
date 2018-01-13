#ifndef QRW_CAMERA_HPP
#define QRW_CAMERA_HPP

#include <SFML/System/Vector2.hpp>

namespace sf {
class RenderTarget;
}

namespace qrw {

class Camera
{
public:
	Camera()
	{}

	virtual ~Camera()
	{}

	virtual void applyTo(sf::RenderTarget& renderTarget) = 0;

private:
	Camera(const Camera& rhs) = delete;

	Camera& operator=(const Camera& rhs) = delete;
};


} // namespace qrw

#endif // QRW_CAMERA_HPP
