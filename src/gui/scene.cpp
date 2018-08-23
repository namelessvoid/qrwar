#include "gui/scene.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/texturemanager.hpp"

#include "engine/terrain.hpp"
#include "engine/unit.hpp"

#include "eventsystem/eventsystem.hpp"
#include "eventsystem/inputevents.hpp"

#include "foundation/spritecomponent.hpp"

namespace qrw
{

Scene::Scene()
{
}

Scene::~Scene()
{
	reset();
}

void Scene::setBoard(Board* board)
{
    _board = board;

	addGameObject(board);
}

void Scene::setRenderTarget(sf::RenderTarget* renderTarget)
{
	_renderTarget = renderTarget;
}

void Scene::destroy(GameObject *gameObject)
{
	m_toDeleteOnNextFrame.insert(gameObject);
	gameObject->onDestroy();
}

void Scene::killPendingGameObjects()
{
	for(auto& gameObject : m_toDeleteOnNextFrame)
	{
		m_gameObjects[typeid(*gameObject)].erase(gameObject);
		delete gameObject;
	}
	m_toDeleteOnNextFrame.clear();
}

void Scene::addGameObject(GameObject* gameObject)
{
	assert(gameObject!=nullptr);

	m_gameObjects[typeid(*gameObject)].insert(gameObject);
	gameObject->onAddToScene();
}

void Scene::reset()
{
	for(auto gameObjectsIter : m_gameObjects)
	{
		for(auto gameObject : gameObjectsIter.second)
		{
			destroy(gameObject);
		}
	}
}

void Scene::update(float elapsedTimeInSeconds)
{
	killPendingGameObjects();

	for(auto& gameObjectsIter : m_gameObjects)
	{
		for(auto& gameObject : gameObjectsIter.second)
		{
			if(!gameObject->isInitialized()) gameObject->initialize();
			gameObject->update(elapsedTimeInSeconds);
		}
	}
}

} // namespace qrw
