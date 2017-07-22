#include "foundation/gameobject.hpp"

#include "foundation/gamecomponent.hpp"

namespace qrw
{

void GameObject::addComponent(qrw::GameComponent* component)
{
	assert(component!=nullptr);
	assert(_components.find(typeid(*component))==_components.end());
	_components[typeid(*component)] = component;
}

} // namespace qrw
