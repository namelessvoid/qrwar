#ifndef QRWAR_SQUAREMARKER_HPP
#define QRWAR_SQUAREMARKER_HPP

#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>

#include "game/skirmish/coordinates.hpp"

#include "foundation/gameobject.hpp"

namespace qrw
{

class SpriteComponent;

class SquareMarker : public GameObject
{
public:
	const SID& getTypeName() const override	{ throw "Not implemented"; }

	SquareMarker();

	Coordinates getBoardPosition() const;

	void setBoardPosition(const Coordinates& boardPosition);

	bool isVisible() const;

	void setVisible(bool visible);

	void markInvalid();
	void markValid();
	void markAttackable();
	void markRangeAttackable();

protected:
	sf::Color m_color;

	Coordinates m_boardPosition;

	SpriteComponent* m_spriteComponent;
};

} // namespace qrw
#endif // QRWAR_SQUAREMARKER_HPP
