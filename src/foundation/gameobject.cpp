#include "foundation/gameobject.hpp"

#include "foundation/gamecomponent.hpp"

#include "gui/scene.hpp"

namespace qrw
{

GameObject::GameObject()
	: initialized_(false)
{
}

GameObject::~GameObject()
{
	for(auto componentIterator : components_)
		delete componentIterator.second;
}

void GameObject::addComponent(GameComponent* component)
{
	assert(component!=nullptr);
	components_.insert(std::pair<std::type_index,GameComponent*>(typeid(*component), component));
}

void GameObject::onDestroy()
{
	for(auto& component : components_)
		component.second->onDestroy();
}


} // namespace qrw
