#include "gui/squaremarker.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "foundation/spritecomponent.hpp"
#include "gui/scene.hpp"

#include "gui/texturemanager.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"
#include "game/skirmish/isometricconversion.hpp"
#include "game/skirmish/structure.hpp"

namespace qrw
{

SquareMarker::SquareMarker()
	: m_boardPosition(0, 0)
{
	m_spriteComponent = new SpriteComponent(*this, RENDER_LAYER_GAME);
	m_spriteComponent->setSize({2.0f * SQUARE_DIMENSION, SQUARE_DIMENSION});
	markValid();
	addComponent(m_spriteComponent);
}

Coordinates SquareMarker::getBoardPosition() const
{
	return m_boardPosition;
}

void SquareMarker::setBoardPosition(const Coordinates& boardPosition)
{
	m_boardPosition = boardPosition;

	float yOffset = 0;
	if(auto board = g_scene.findSingleGameObject<Board>()) {
		if(auto structure = board->getStructure(m_boardPosition)) {
			yOffset = structure->getCurrentVisualHeightForUnits();
		}
	}

	auto isoPosition = worldToIso({SQUARE_DIMENSION * m_boardPosition.getX(), SQUARE_DIMENSION * m_boardPosition.getY()});

	m_spriteComponent->setOrigin(SQUARE_DIMENSION, 0.0f);
	m_spriteComponent->setPosition(isoPosition + sf::Vector2f(0, yOffset));
	m_spriteComponent->setZIndex(isoPosition.y + 0.2f);
}

bool SquareMarker::isVisible() const
{
	return m_spriteComponent->isVisible();
}

void SquareMarker::setVisible(bool visible)
{
	m_spriteComponent->setVisible(visible);
}

void SquareMarker::markValid()
{
	m_spriteComponent->setTexture(TextureManager::getInstance()->getTexture("squaremarker"));
}

void SquareMarker::markInvalid()
{
	m_spriteComponent->setTexture(TextureManager::getInstance()->getTexture("squaremarkerinvalid"));
}

} // namespace qrw
