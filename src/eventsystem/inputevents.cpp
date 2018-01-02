#include "eventsystem/inputevents.hpp"

namespace qrw
{

template<>
const SID EventBase<MouseMovedEvent>::name("MOUSE_MOVED");

template<>
const SID EventBase<LeftMouseButtonPressedEvent>::name("LEFT_MOUSE_BUTTON_PRESSED");

template<>
const SID EventBase<RightMouseButtonPressedEvent>::name("RIGHT_MOUSE_BUTTON_PRESSED");

template<>
const SID EventBase<LeftMouseButtonReleasedEvent>::name("LEFT_MOUSE_BUTTON_RELEASED");

template<>
const SID EventBase<RightMouseButtonReleasedEvent>::name("RIGHT_MOUSE_BUTTON_RELEASED");

template<>
const SID EventBase<KeyPressedEvent>::name("KEY_PRESSED");

} // namespace qrw
