#ifndef QRW_GAMEOBJECT_HPP
#define QRW_GAMEOBJECT_HPP

#include <map>
#include <typeinfo>
#include <typeindex>
#include <cassert>
#include <functional>

#include <foundation/gamecomponent.hpp>

#include "meta/reflectable.hpp"

namespace qrw
{

class GameComponent;

class GameObject : public Reflectable
{
public:
	GameObject();

	~GameObject() override;

	virtual void onDestroy() {}

	virtual void onAddToScene() {}

	virtual void initialize() { initialized_ = true; }
	bool isInitialized() { return initialized_; }

	void addComponent(GameComponent* component);

	virtual void update(float elapsedTimeInSeconds) {}

	template<class T>
	T* getComponent();

private:
	bool initialized_;

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
