#ifndef QRW_SQUARESELECTION_HPP
#define QRW_SQUARESELECTION_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <memory>

#include "game/skirmish/coordinates.hpp"
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
	const SID& getTypeName() const override	{ throw "Not implemented"; }

	Cursor();

	virtual ~Cursor();

	virtual bool handleEvent(const qrw::IEvent& event) override;
};

} // namespace qrw

#endif
