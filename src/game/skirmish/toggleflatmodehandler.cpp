#include "eventsystem/inputevents.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/unit.hpp"
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

template<class T>
void toggleFlatModeFor(bool isFlatMode)
{
	auto gameObjects = g_scene.findGameObjects<T>();

	for(auto& gameObject : gameObjects) {
		auto* flatModeAwareGameObject = dynamic_cast<FlatModeAwareMixin*>(gameObject);
		assert(flatModeAwareGameObject != nullptr);
		flatModeAwareGameObject->setFlatMode(isFlatMode);
	}
}

void ToggleFlatModeHandler::toggleFlatMode()
{
	isFlatMode_ = !isFlatMode_;
	toggleFlatModeFor<Wall>(isFlatMode_);
	toggleFlatModeFor<Unit>(isFlatMode_);
}

} // namespace qrw