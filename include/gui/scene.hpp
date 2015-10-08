#ifndef QRW_SCENE_HPP
#define QRW_SCENE_HPP

#include <map>
#include <memory>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "engine/board.hpp"
#include "gui/cursor.hpp"
#include "gui/terrainentity.hpp"
#include "gui/unitentity.hpp"
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
	Scene(sf::RenderTarget* rendertarget, Board::Ptr board);

	~Scene();

	void render();

	void handleEvent(const sf::Event& event);

	namelessgui::Signal<Coordinates> signalCursorLeftClicked;
	namelessgui::Signal<Coordinates> signalCursorRightClicked;

	void addTerrainEntity(TerrainEntity::Ptr terrainEntity);
	void removeTerrainEntityAt(const Coordinates& boardPosition);

	void addUnitEntity(UnitEntity::Ptr unitEntity);

private:
	sf::RenderTarget* _renderTarget;

	Board::Ptr _board;

	sf::RectangleShape _background;
	Cursor _cursor;

	std::map<const Coordinates, TerrainEntity::Ptr> _terrainEntities;
	std::map<const Coordinates, UnitEntity::Ptr> _unitEntities;
};

} // namespace qrw

#endif // QRW_SCENE_HPP
