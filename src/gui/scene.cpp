#include "gui/scene.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/texturemanager.hpp"

#include "engine/terrain.hpp"
#include "engine/unit.hpp"

#include "foundation/spritecomponent.hpp"

namespace qrw
{

Scene::Scene(sf::RenderTarget* renderTarget)
    : _renderTarget(renderTarget)
{
}

Scene::~Scene()
{
}

void Scene::setBoard(Board::Ptr board)
{
    _board = board;

    // Set up background
    _background.setTexture(TextureManager::getInstance()->getTexture("plainsquare"));

    sf::Vector2u spriteSize = _background.getTexture()->getSize();
    sf::Vector2f backgroundSize = sf::Vector2f(board->getWidth() * spriteSize.x, board->getHeight() * spriteSize.y);
    _background.setSize(backgroundSize);
    _background.setTextureRect(sf::IntRect(0, 0, backgroundSize.x, backgroundSize.y));

    // Set up corser and connect cursor slots
    _cursor.setBoard(board);
    _cursor.signalLeftClicked.connect(std::bind(&namelessgui::Signal<Coordinates>::emit, &signalCursorLeftClicked, std::placeholders::_1));
    _cursor.signalRightClicked.connect(std::bind(&namelessgui::Signal<Coordinates>::emit, &signalCursorRightClicked, std::placeholders::_1));
    _cursor.signalMoved.connect(std::bind(&namelessgui::Signal<Coordinates,bool>::emit, &signalCursorMoved, std::placeholders::_1, std::placeholders::_2));
}

void Scene::render()
{
	sf::RenderStates renderStates = sf::RenderStates::Default;

	_renderTarget->draw(_background, renderStates);

	for(auto terrainIterator : _board->getTerrains())
		terrainIterator.second->getComponent<SpriteComponent>()->render(_renderTarget);

	for(auto unitIterator : _board->getUnits())
		unitIterator.second->getComponent<SpriteComponent>()->render(_renderTarget);

	_renderTarget->draw(_cursor, renderStates);
}

void Scene::handleEvent(const sf::Event& event)
{
	sf::Event adjustedEvent = event;

	// If mouse moved, convert screen coordinates to world coordinates
	if(event.type == sf::Event::MouseMoved)
	{
		sf::Vector2i mousePixelCoordinates(event.mouseMove.x, event.mouseMove.y);
		sf::Vector2f mouseWorldCoordinates = _renderTarget->mapPixelToCoords(mousePixelCoordinates);

		adjustedEvent.mouseMove.x = mouseWorldCoordinates.x;
		adjustedEvent.mouseMove.y = mouseWorldCoordinates.y;
	}

	// Propagate events
    _cursor.handleEvent(adjustedEvent);
}

Coordinates Scene::getCursorPosition()
{
	return _cursor.getBoardPosition();
}

Cursor& Scene::getCursor()
{
	return _cursor;
}


} // namespace qrw
