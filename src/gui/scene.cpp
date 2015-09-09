#include "gui/scene.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "gui/texturemanager.hpp"

namespace qrw
{

Scene::Scene(sf::RenderTarget* renderTarget, Board::Ptr board)
	: _renderTarget(renderTarget)
{
	// Set up background
	_background.setTexture(TextureManager::getInstance()->getTexture("plainsquare"));

	sf::Vector2u spriteSize = _background.getTexture()->getSize();
	sf::Vector2f backgroundSize = sf::Vector2f(board->getWidth() * spriteSize.x, board->getHeight() * spriteSize.y);
	_background.setSize(backgroundSize);
	_background.setTextureRect(sf::IntRect(0, 0, backgroundSize.x, backgroundSize.y));

	_cursor.setBoard(board);
	_cursor.signalLeftClicked.connect(std::bind(&namelessgui::Signal<Coordinates>::emit, &signalCursorLeftClicked, std::placeholders::_1));
	_cursor.signalRightClicked.connect(std::bind(&namelessgui::Signal<Coordinates>::emit, &signalCursorRightClicked, std::placeholders::_1));
}

Scene::~Scene()
{
}

void Scene::render()
{
	sf::RenderStates renderStates = sf::RenderStates::Default;

	_renderTarget->draw(_background, renderStates);
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


} // namespace qrw
