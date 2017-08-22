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

	void render();

	void handleEvent(const sf::Event& event);

	void addGameObject(GameObject* gameObject);

	void removeGameObject(GameObject* gameObject);

	template<class T>
	std::set<GameObject*>& getGameObjects();

	template<class T>
	T* getSingleGameObject();

	void reset();

private:
	sf::RenderTarget* _renderTarget;

	Board* _board;

	std::map<std::type_index,std::set<GameObject*>> m_gameObjects;
};

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
