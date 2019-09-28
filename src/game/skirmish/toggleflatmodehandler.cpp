#include "eventsystem/inputevents.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/toggleflatmodehandler.hpp"

namespace qrw
{

ToggleFlatModeHandler::ToggleFlatModeHandler() : EventHandler(0)
{}

bool ToggleFlatModeHandler::handleEvent(const IEvent& event)
{
	if(event.getName() == KeyPressedEvent::name) {
		if(static_cast<const KeyPressedEvent&>(event).key == KeyboardKey::Space) {
			toggleFlatMode();
		}
	}

	return false;
}

void ToggleFlatModeHandler::toggleFlatMode()
{
	isFlatMode_ = !isFlatMode_;
	auto wallGameObjects = g_scene.findGameObjects<Wall>();

	for(auto& wallGameObject : wallGameObjects) {
		Wall* wall = static_cast<Wall*>(wallGameObject);
		wall->setFlatMode(isFlatMode_);
	}
}

} // namespace qrw