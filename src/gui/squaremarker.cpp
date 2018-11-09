#include "gui/squaremarker.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "foundation/spritecomponent.hpp"

#include "gui/texturemanager.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"

namespace qrw
{

SquareMarker::SquareMarker()
	: m_boardPosition(0, 0)
{
	m_spriteComponent = new SpriteComponent(RENDER_LAYER_CURSOR);
	m_spriteComponent->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
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

	float dimension = m_spriteComponent->getSize().x;

	m_spriteComponent->setPosition({dimension * m_boardPosition.getX(), dimension * m_boardPosition.getY()});
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

} // namespace qrw
