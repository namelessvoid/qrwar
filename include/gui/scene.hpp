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
#include "game/skirmish/coordinates.hpp"


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
	std::set<GameObject*> findGameObjects();

	template<class TGameObject>
	TGameObject* findSingleGameObject();

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
std::set<GameObject*> Scene::findGameObjects()
{
	auto iter = m_gameObjects.find(typeid(T));

	if(iter == m_gameObjects.end())
		return {};

	return iter->second;
}

template<class TGameObject>
TGameObject* Scene::findSingleGameObject()
{
	auto gameObjects = findGameObjects<TGameObject>();
	if (gameObjects.size() == 0)
		return nullptr;
	return static_cast<TGameObject*>(*gameObjects.begin());
}

extern Scene g_scene;

} // namespace qrw

#endif // QRW_SCENE_HPP
