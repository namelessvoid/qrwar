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

	// Called by Scene::destroy(GameObject*).
	// This is useful to clean up resources which have to call other game objects in the cleanup process.
	// The GameObject is not destroyed immediately but is scheduled for deletion on the
	// next frame.
	virtual void onDestroy();

	// Called by Scene::addtoScene(GameObject*).
	virtual void onAddToScene() {}

	// Called by Scene::update() right before the GameObject's update method would
	// be called for the first time.
	// This is useful for e.g. initializing resources which depend on other game objects and therefore
	// cannot be initialized in the constructor since not all scene objects my be created yet.
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
