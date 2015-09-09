#ifndef QRW_SCENE_HPP
#define QRW_SCENE_HPP

#include <map>
#include <memory>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/board.hpp"
#include "gui/cursor.hpp"
#include "gui/ng/signal.hpp"

// Foreward declarations
namespace sf
{
class RenderTarget;
}


namespace qrw
{

class Scene
{
public:
	Scene(Board::Ptr board);

	~Scene();

	void render(sf::RenderTarget& renderTarget, sf::RenderStates renderStates = sf::RenderStates::Default);

	void handleEvent(const sf::Event& event);

	namelessgui::Signal<Coordinates> signalCursorLeftClicked;
	namelessgui::Signal<Coordinates> signalCursorRightClicked;

private:
	sf::RectangleShape _background;
	Cursor _cursor;
};

} // namespace qrw

#endif // QRW_SCENE_HPP
