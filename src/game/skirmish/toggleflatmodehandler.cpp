#include "game/skirmish/toggleflatmodehandler.hpp"

#include "eventsystem/inputevents.hpp"
#include "game/deploymentzone.hpp"
#include "game/skirmish/wall.hpp"
#include "game/skirmish/unit.hpp"
#include "game/skirmish/laddercarrier.hpp"
#include "game/skirmish/archer.hpp"
#include "game/skirmish/stairs.hpp"

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
		auto* concreteGameObject = dynamic_cast<T*>(gameObject);
		concreteGameObject->setFlatMode(isFlatMode);
	}
}

void ToggleFlatModeHandler::toggleFlatMode()
{
	isFlatMode_ = !isFlatMode_;
	toggleFlatModeFor<Wall>(isFlatMode_);
	toggleFlatModeFor<Stairs>(isFlatMode_);
	toggleFlatModeFor<DeploymentZone>(isFlatMode_);
	toggleFlatModeFor<Unit>(isFlatMode_);
	toggleFlatModeFor<LadderCarrier>(isFlatMode_);
	toggleFlatModeFor<Archer>(isFlatMode_);
}

} // namespace qrw