#include "gui/squaremarker.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "foundation/spritecomponent.hpp"

#include "gui/texturemanager.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"
#include "game/skirmish/isometricconversion.hpp"

namespace qrw
{

SquareMarker::SquareMarker()
	: m_boardPosition(0, 0)
{
	m_spriteComponent = new SpriteComponent(RENDER_LAYER_CURSOR);
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

	m_spriteComponent->setOrigin(SQUARE_DIMENSION, 0.0f);
	m_spriteComponent->setPosition(worldToIso({SQUARE_DIMENSION * m_boardPosition.getX(), SQUARE_DIMENSION * m_boardPosition.getY()}));
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

void SquareMarker::markAttackable()
{
	m_spriteComponent->setTexture(TextureManager::getInstance()->getTexture("squaremarkerattack"));
}

void SquareMarker::markRangeAttackable()
{
	m_spriteComponent->setTexture(TextureManager::getInstance()->getTexture("squaremarkerrangeattack"));
}

void SquareMarker::markDeployLadder()
{
	m_spriteComponent->setTexture(TextureManager::getInstance()->getTexture("squaremarkerdeployladder"));
}

} // namespace qrw
