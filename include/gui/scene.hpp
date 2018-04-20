#ifndef QRW_SCENE_HPP
#define QRW_SCENE_HPP

#include <cassert>
#include <map>
#include <set>
#include <memory>
#include <typeindex>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/board.hpp"
#include "engine/coordinates.hpp"


// Foreward declarations
namespace sf
{
class RenderTarget;
class Event;
}


namespace qrw
{

class GameObject;

class Scene
{
public:
	Scene();

	~Scene();

	void setBoard(Board* board);

	void setRenderTarget(sf::RenderTarget* renderTarget);

	template<class TGameObject>
	TGameObject* spawn();

	void addGameObject(GameObject* gameObject);

	void destroy(GameObject* gameObject);

	template<class TGameObject>
	std::set<GameObject*>& getGameObjects();

	template<class TGameObject>
	TGameObject* getSingleGameObject();

	void reset();

	void update(float elapsedTimeInSeconds);

private:
	void killPendingGameObjects();

	sf::RenderTarget* _renderTarget;

	Board* _board;

	std::map<std::type_index,std::set<GameObject*>> m_gameObjects;

	std::set<GameObject*> m_toDeleteOnNextFrame;
};

template<class TGameObject>
TGameObject *Scene::spawn()
{
	TGameObject* gameObject = new TGameObject();
	addGameObject(gameObject);
	return gameObject;
}

template<class T>
std::set<GameObject*>& Scene::getGameObjects()
{
	assert(m_gameObjects.find(typeid(T))!=m_gameObjects.end());
	return m_gameObjects.find(typeid(T))->second;
}

template<class T>
T* Scene::getSingleGameObject()
{
	auto gameObjects = getGameObjects<T>();

	assert(gameObjects.size()==1);

	return static_cast<T*>(*gameObjects.begin());
}

extern Scene g_scene;

} // namespace qrw

#endif // QRW_SCENE_HPP
