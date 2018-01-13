#ifndef QRW_BIRDSEYECAMERA_HPP
#define QRW_BIRDSEYECAMERA_HPP

#include <SFML/System/Vector2.hpp>

#include "camera.hpp"

#include "eventsystem/eventhandler.hpp"

namespace qrw {

class BirdsEyeCamera : public Camera, public EventHandler
{
public:
    BirdsEyeCamera();

    virtual ~BirdsEyeCamera();

    void setCenter(const sf::Vector2f& center) { center_ = center; }

    virtual void applyTo(sf::RenderTarget& renderTarget) override;

    virtual bool handleEvent(const IEvent &event) override;

private:
    sf::Vector2f center_;

    BirdsEyeCamera(const BirdsEyeCamera& rhs) = delete;

    BirdsEyeCamera& operator=(const BirdsEyeCamera& rhs) = delete;
};


} // namespace qrw

#endif // QRW_BIRDSEYECAMERA_HPP
