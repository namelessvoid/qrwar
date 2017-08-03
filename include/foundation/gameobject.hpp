#ifndef QRW_GAMEOBJECT_HPP
#define QRW_GAMEOBJECT_HPP

#include <map>
#include <typeinfo>
#include <typeindex>
#include <cassert>
#include <functional>

#include <foundation/gamecomponent.hpp>

namespace qrw
{

class GameComponent;

class GameObject
{
public:
	virtual ~GameObject();

	void addComponent(GameComponent* component);

	template<class T>
	T* getComponent();

	std::map<std::type_index, GameComponent*> _components;
};

template<class T>
T* GameObject::getComponent()
{
	assert(_components.find(typeid(T))!=_components.end());
	return dynamic_cast<T*>(_components.at(typeid(T)));
}

} // namespace qrw

#endif // QRW_GAMEOBJECT_HPP