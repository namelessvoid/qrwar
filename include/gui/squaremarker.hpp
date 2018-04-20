#ifndef QRWAR_SQUAREMARKER_HPP
#define QRWAR_SQUAREMARKER_HPP

#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/coordinates.hpp"

#include "foundation/gameobject.hpp"

namespace qrw
{

class SpriteComponent;

class SquareMarker : public GameObject
{
public:
	SquareMarker();

	virtual ~SquareMarker() {}

	void setDimensions(float dimensions);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	Coordinates getBoardPosition() const;

	void setBoardPosition(const Coordinates& boardPosition);

	bool isVisible() const;

	void setVisible(bool visible);

	void markInvalid();
	void markValid();

protected:
	sf::Color m_color;

	Coordinates m_boardPosition;

	SpriteComponent* m_spriteComponent;
};

} // namespace qrw
#endif // QRWAR_SQUAREMARKER_HPP
