#ifndef QRW_SQUARESELECTION_HPP
#define QRW_SQUARESELECTION_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>

#include "engine/coordinates.hpp"
#include "gui/squaremarker.hpp"

#include "eventsystem/eventhandler.hpp"

#include "foundation/gameobject.hpp"

namespace sf
{
class Event;
}

namespace qrw
{
class Board;

class Cursor : public SquareMarker, public EventHandler
{
public:
	enum class Color
	{
		ESC_DEFAULT,
		ESC_WARNING,
		ESC_DANGER
	};

	Cursor();

	virtual ~Cursor();

	virtual bool handleEvent(const qrw::IEvent& event) override;

	void setFillColor(Color color);
};
} // namespace qrw

#endif
