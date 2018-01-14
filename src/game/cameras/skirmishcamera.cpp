#include "game/cameras/skirmishcamera.hpp"

#include "eventsystem/inputevents.hpp"

#include "rendering/rendersystem.hpp"

namespace qrw
{

SkirmishCamera::SkirmishCamera()
	: currentMovementDirection_(0, 0)
{
}

SkirmishCamera::~SkirmishCamera()
{
}

void SkirmishCamera::update(float elapsedTimeInSeconds)
{
	BirdsEyeCamera& camera = g_renderSystem.getCamera();
	camera.setCenter(camera.getCenter() + currentMovementDirection_ * (SCROLL_SPEED * elapsedTimeInSeconds));
}

bool SkirmishCamera::handleEvent(const IEvent &event)
{
	if(event.getName() == KeyPressedEvent::name)
	{
		KeyboardKey key = static_cast<const KeyPressedEvent&>(event).key;

		switch(key)
		{
		case KeyboardKey::Right: //ft
		case KeyboardKey::D:
			currentMovementDirection_.x = 1;
			break;
		case KeyboardKey::Left: // ft
		case KeyboardKey::A:
			currentMovementDirection_.x = -1;
			break;
		case KeyboardKey::Up: //ft
		case KeyboardKey::W:
			currentMovementDirection_.y = -1;
			break;
		case KeyboardKey::Down: // ft
		case KeyboardKey::S:
			currentMovementDirection_.y = 1;
			break;
		default:
			break;
		}
	}
	else if(event.getName() == KeyReleasedEvent::name)
	{
		KeyboardKey key = static_cast<const KeyReleasedEvent&>(event).key;

		switch (key) {
		case KeyboardKey::Right: // ft
		case KeyboardKey::Left: // ft
		case KeyboardKey::D: // ft
		case KeyboardKey::A:
			currentMovementDirection_.x = 0;
			break;
		case KeyboardKey::Up: // ft
		case KeyboardKey::Down: // ft
		case KeyboardKey::W: //ft
		case KeyboardKey::S:
			currentMovementDirection_.y = 0;
			break;
		default:
			break;
		}
	}

	return false;
}

} // namespace qrw
