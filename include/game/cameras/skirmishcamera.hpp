#ifndef QRW_SKIRMISHCAMERA_HPP
#define QRW_SKIRMISHCAMERA_HPP

#include <SFML/System/Vector2.hpp>

#include "foundation/gameobject.hpp"

#include "eventsystem/eventhandler.hpp"

namespace qrw {

class SkirmishCamera : public GameObject, public EventHandler
{
public:
	const SID& getTypeName() const override	{ throw "Not implemented"; }

    SkirmishCamera();

    ~SkirmishCamera();

    virtual void update(float elapsedTimeInSeconds) override;

    virtual bool handleEvent(const IEvent &event) override;

    void setCenter(sf::Vector2f center);

private:
    sf::Vector2f currentMovementDirection_;

    const float SCROLL_SPEED = 500.0f;

    SkirmishCamera(const SkirmishCamera& rhs) = delete;

    SkirmishCamera& operator=(const SkirmishCamera& rhs) = delete;
};


} // namespace qrw

#endif // QRW_SKIRMISHCAMERA_HPP
