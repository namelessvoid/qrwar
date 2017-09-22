#include "foundation/gameobject.hpp"

#include "foundation/gamecomponent.hpp"

#include "gui/scene.hpp"

namespace qrw
{

GameObject::~GameObject()
{
	for(auto componentIterator : _components)
		delete componentIterator.second;
}

void GameObject::addComponent(qrw::GameComponent* component)
{
	assert(component!=nullptr);
	assert(_components.find(typeid(*component))==_components.end());
	_components[typeid(*component)] = component;
}

} // namespace qrw
