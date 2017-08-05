#ifndef QRW_SQUARESELECTION_HPP
#define QRW_SQUARESELECTION_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>

#include "engine/coordinates.hpp"
#include "gui/squaremarker.hpp"

namespace sf
{
class Event;
}

namespace qrw
{
class Board;

class Cursor : public SquareMarker
{
public:
	enum class Color
	{
		ESC_DEFAULT,
		ESC_WARNING,
		ESC_DANGER
	};

	Cursor();

	~Cursor();

	void handleEvent(const sf::Event& event);

	void setFillColor(Color color);
};
} // namespace qrw

#endif
