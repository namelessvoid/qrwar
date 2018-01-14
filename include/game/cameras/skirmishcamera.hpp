#ifndef QRW_SKIRMISHCAMERA_HPP
#define QRW_SKIRMISHCAMERA_HPP

#include "foundation/gameobject.hpp"

#include "eventsystem/eventhandler.hpp"

namespace qrw {

class SkirmishCamera : public GameObject, public EventHandler
{
public:
    SkirmishCamera();

    ~SkirmishCamera();

    virtual void update() override;

    virtual bool handleEvent(const IEvent &event) override;

private:
    SkirmishCamera(const SkirmishCamera& rhs) = delete;

    SkirmishCamera& operator=(const SkirmishCamera& rhs) = delete;
};


} // namespace qrw

#endif // QRW_SKIRMISHCAMERA_HPP
