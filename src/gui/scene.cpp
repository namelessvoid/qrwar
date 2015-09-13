#include "gui/scene.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/texturemanager.hpp"

#include "engine/square.hpp"

namespace qrw
{

Scene::Scene(sf::RenderTarget* renderTarget, Board::Ptr board)
	: _renderTarget(renderTarget),
	  _board(board)
{
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

	// Initialize entities
	Square* square;
	for(int r = 0; r < _board->getHeight(); ++r)
	{
		for(int c = 0; c < _board->getWidth(); ++c)
		{
			square = _board->getSquare(c, r);

			// Add terrain entities
			if(square->getTerrain() != nullptr)
				addTerrainEntity(TerrainEntity::createTerrainEntity(square->getTerrain(), 32));

			// Add unit enitity
			// TODO...
		}
	}
}

Scene::~Scene()
{
}

void Scene::render()
{
	sf::RenderStates renderStates = sf::RenderStates::Default;

	_renderTarget->draw(_background, renderStates);

	for(auto entityIterator : _terrainEntities)
		_renderTarget->draw(*(entityIterator.second));

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

void Scene::addTerrainEntity(TerrainEntity::Ptr terrainEntity)
{
	_terrainEntities[terrainEntity->getBoardPosition()] = terrainEntity;
}

void Scene::removeTerrainEntityAt(const Coordinates& boardPosition)
{
	_terrainEntities.erase(boardPosition);
}


} // namespace qrw
