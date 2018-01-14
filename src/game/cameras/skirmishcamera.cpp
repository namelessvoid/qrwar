#include "game/cameras/skirmishcamera.hpp"

#include "eventsystem/inputevents.hpp"

#include "rendering/rendersystem.hpp"

namespace qrw
{

SkirmishCamera::SkirmishCamera()
{
}

SkirmishCamera::~SkirmishCamera()
{
}

void SkirmishCamera::update()
{
}

bool SkirmishCamera::handleEvent(const IEvent &event)
{
	if(event.getName() == KeyPressedEvent::name)
	{
		KeyPressedEvent::Key key = static_cast<const KeyPressedEvent&>(event).key;

		sf::Vector2f movementDirection(0, 0);
		BirdsEyeCamera& camera = g_renderSystem.getCamera();

		switch(key)
		{
		case KeyPressedEvent::Key::Right: //ft
		case KeyPressedEvent::Key::D:
			++movementDirection.x;
			break;
		case KeyPressedEvent::Key::Left: // ft
		case KeyPressedEvent::Key::A:
			--movementDirection.x;
			break;
		case KeyPressedEvent::Key::Up: //ft
		case KeyPressedEvent::Key::W:
			--movementDirection.y;
			break;
		case KeyPressedEvent::Key::Down: // ft
		case KeyPressedEvent::Key::S:
			++movementDirection.y;
			break;
		default:
			break;
		}

		camera.setCenter(camera.getCenter() + movementDirection * 10.0f);
	}
	return false;
}

} // namespace qrw
