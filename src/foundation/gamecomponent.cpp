#include "foundation/gamecomponent.hpp"

namespace qrw {

GameComponent::GameComponent(GameObject& owner)
	: owner_(&owner)
{
}

}