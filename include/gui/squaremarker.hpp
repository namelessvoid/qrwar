#ifndef QRWAR_SQUAREMARKER_HPP
#define QRWAR_SQUAREMARKER_HPP

#include <memory>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/coordinates.hpp"

namespace qrw
{

class Board;

class SquareMarker : public sf::RectangleShape
{
public:
	SquareMarker();

	virtual ~SquareMarker() {}

	void setBoard(std::shared_ptr<Board> spBoard);

	void setDimensions(float dimensions);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	Coordinates getBoardPosition() const;

	void setBoardPosition(const Coordinates& boardPosition);

	bool isVisible() const;

	void setVisible(bool visible);

protected:
	sf::Color _color;

	Coordinates _boardPosition;

	std::shared_ptr<Board> _board;

	bool _visible;
};

} // namespace qrw
#endif // QRWAR_SQUAREMARKER_HPP
