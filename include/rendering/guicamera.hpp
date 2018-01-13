#ifndef QRW_GUICAMERA_HPP
#define QRW_GUICAMERA_HPP

#include "camera.hpp"

namespace qrw {

class GuiCamera : public Camera
{
public:
    GuiCamera();

    virtual ~GuiCamera();

    virtual void applyTo(sf::RenderTarget& renderTarget) override;

private:
    GuiCamera(const GuiCamera& rhs) = delete;

    GuiCamera& operator=(const GuiCamera& rhs) = delete;
};


} // namespace qrw

#endif // QRW_GUICAMERA_HPP
