#ifndef QRW_SQUARESELECTION_HPP
#define QRW_SQUARESELECTION_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>

#include "engine/coordinates.hpp"
#include "gui/ng/signal.hpp"
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

	// signals
	namelessgui::Signal<const Coordinates&> signalLeftClicked;
	namelessgui::Signal<const Coordinates&> signalRightClicked;

    /**
     * @brief Signal emitted when the cursor moved to a new board position.
     *
     * First parameter are the new coordinates on the board.
     * Second parameter is set to false when the cursor left the board and true if
     * cursor is on the board.
     */
    namelessgui::Signal<const Coordinates&, bool> signalMoved;

	void setFillColor(Color color);
};
} // namespace qrw

#endif
