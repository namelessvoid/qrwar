#ifndef QRW_SQUARESELECTION_HPP
#define QRW_SQUARESELECTION_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>

#include "engine/coordinates.hpp"
#include "gui/ng/signal.hpp"

namespace sf
{
class Event;
}

namespace qrw
{
class Board;

class Cursor : public sf::RectangleShape
{
public:
	Cursor();
	static Cursor* getCursor();

	~Cursor();

	void setBoard(std::shared_ptr<Board> spBoard);

	void setDimensions(float _dimensions);

	/**
	 * @argument position Position on the screen (pixles)
	 * @argument size Size of the cursor on the screen in pixles.
	 */
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void handleEvent(const sf::Event& event);

	// signals
	namelessgui::Signal<> signalLeftClicked;
	namelessgui::Signal<> signalRightClicked;

private:
	sf::Color _maincolor;
	bool _visible;

	Coordinates _boardPosition;
	std::shared_ptr<Board> _spBoard;
};
}

#endif
