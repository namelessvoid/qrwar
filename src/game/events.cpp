#include "game/events.hpp"

namespace qrw
{

template<>
const SID EventBase<CursorMovedEvent>::name("CURSOR_MOVED");

template<>
const SID EventBase<CursorLeftClickedEvent>::name("CURSOR_LEFT_CLICKED");

template<>
const SID EventBase<CursorRightClickedEvent>::name("CURSOR_RIGHT_CLICKED");

} // namespace qrw
