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
}

Scene::~Scene()
{
}

void Scene::render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates)
{
	renderTarget.draw(_background, renderStates);
}


} // namespace qrw
