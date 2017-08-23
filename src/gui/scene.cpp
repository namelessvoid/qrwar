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

void Scene::addGameObject(GameObject* gameObject)
{
	assert(gameObject!=nullptr);

	m_gameObjects[typeid(*gameObject)].insert(gameObject);
}

void Scene::removeGameObject(GameObject *gameObject)
{
	assert(gameObject!=nullptr);

	m_gameObjects[typeid(*gameObject)].erase(gameObject);
}

void Scene::reset()
{
	for(auto gameObjectsIter : m_gameObjects)
	{
		for(auto gameObject : gameObjectsIter.second)
		{
			delete gameObject;
		}
	}
	m_gameObjects.clear();
}

} // namespace qrw
