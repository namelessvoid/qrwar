#ifndef QRW_SCENE_HPP
#define QRW_SCENE_HPP

#include <map>
#include <memory>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/board.hpp"
#include "engine/coordinates.hpp"

#include "gui/cursor.hpp"
#include "gui/terrainentity.hpp"
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
    Scene(sf::RenderTarget* rendertarget);

	~Scene();

    void setBoard(Board::Ptr board);

	void render();

	void handleEvent(const sf::Event& event);

	namelessgui::Signal<Coordinates> signalCursorLeftClicked;
	namelessgui::Signal<Coordinates> signalCursorRightClicked;
    namelessgui::Signal<Coordinates, bool> signalCursorMoved;

	void addTerrainEntity(TerrainEntity::Ptr terrainEntity);
	void removeTerrainEntityAt(const Coordinates& boardPosition);

    Coordinates getCursorPosition();

	Cursor& getCursor();

private:
	sf::RenderTarget* _renderTarget;

	Board::Ptr _board;

	sf::RectangleShape _background;
	Cursor _cursor;

	std::map<const Coordinates, TerrainEntity::Ptr> _terrainEntities;
};

} // namespace qrw

#endif // QRW_SCENE_HPP
