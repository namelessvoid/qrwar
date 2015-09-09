#include "gui/scene.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "gui/texturemanager.hpp"

namespace qrw
{

Scene::Scene(Board::Ptr board)
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

void Scene::render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)
{
	renderTarget.draw(_background, renderStates);
	renderTarget.draw(_cursor, renderStates);
}

void Scene::handleEvent(const sf::Event& event)
{
	_cursor.handleEvent(event);
}


} // namespace qrw
