#include "gui/squaremarker.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "foundation/spritecomponent.hpp"

#include "game/renderlayers.hpp"
#include "game/constants.hpp"

namespace qrw
{

SquareMarker::SquareMarker()
	: m_boardPosition(0, 0)
{
	m_spriteComponent = new SpriteComponent(RENDER_LAYER_CURSOR);
	m_spriteComponent->setFillColor(sf::Color(218, 218, 0, 120));
	m_spriteComponent->setSize({SQUARE_DIMENSION, SQUARE_DIMENSION});
	addComponent(m_spriteComponent);
}

void SquareMarker::setDimensions(float dimensions)
{
	m_spriteComponent->setSize({dimensions, dimensions});
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

} // namespace qrw
