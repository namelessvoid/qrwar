#include "rendering/birdseyecamera.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "eventsystem/inputevents.hpp"

namespace qrw
{

BirdsEyeCamera::BirdsEyeCamera()
	: center_(0, 0)
{
}

BirdsEyeCamera::~BirdsEyeCamera()
{
}

void BirdsEyeCamera::applyTo(sf::RenderTarget& renderTarget)
{
	sf::View view = renderTarget.getView();
	view.setCenter(center_);
	renderTarget.setView(view);
}

bool BirdsEyeCamera::handleEvent(const IEvent& event)
{
	if(event.getName() == KeyPressedEvent::name)
	{
		KeyPressedEvent::Key key = static_cast<const KeyPressedEvent&>(event).key;

		sf::Vector2f movementDirection(0, 0);

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

		center_ += movementDirection * 10.0f;
	}
	return false;
}

} // namespace qrw
