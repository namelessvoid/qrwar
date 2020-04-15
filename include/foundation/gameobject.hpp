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

	virtual void onDestroy();

	virtual void onAddToScene() {}

	virtual void initialize() { initialized_ = true; }
	bool isInitialized() { return initialized_; }

	void addComponent(GameComponent* component);
	void removeComponent(GameComponent* component);

	virtual void update(float elapsedTimeInSeconds) {}

	template<class T>
	T* getFirstComponent();

private:
	bool initialized_;

	std::multimap<std::type_index, GameComponent*> components_;
};

template<class T>
T* GameObject::getFirstComponent()
{
	assert(components_.find(typeid(T))!=components_.end());
	return dynamic_cast<T*>(components_.find(typeid(T))->second);
}

} // namespace qrw

#endif // QRW_GAMEOBJECT_HPP
