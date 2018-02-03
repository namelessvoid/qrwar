#ifndef QRW_MOUSE_HPP
#define QRW_MOUSE_HPP

#include <cassert>

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Mouse.hpp>

namespace qrw
{

class Mouse
{
public:
	// Mouse is a pure static class.
	Mouse() = delete;
	Mouse(const Mouse&) = delete;
	~Mouse()= delete;

	static sf::Vector2i getPosition()
	{
		assert(window_ != nullptr);
		return sf::Mouse::getPosition(*window_);
	}

	static void setWindow(const sf::Window& window) { window_ = &window; }

private:
	static const sf::Window* window_;


};

} // namespace qrw

#endif // QRW_MOUSE_HPP
