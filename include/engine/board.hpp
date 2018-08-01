#ifndef QRW_BOARD_HPP
#define QRW_BOARD_HPP

#include <memory>
#include <map>

#include <SFML/System/Vector2.hpp>

#include "foundation/gameobject.hpp"

#include "core/sid.hpp"

#include "game/skirmish/pathfinding/boardworldadapter.hpp"

namespace qrw
{

namespace pathfinding
{
template<class TSpatialRepresentation>
class AbstractPathfinder;

class Path;
}

class Coordinates;
class Unit;
class Terrain;
class Structure;
class SpriteComponent;

	class Board : public GameObject
	{
		public:
			friend class BoardMetaClass;

			Board()
				: Board(0, 0)
			{}

			Board(unsigned int width, unsigned int height);
			~Board() override;

			void onAddToScene() override;

			void setUnit(const Coordinates& position, Unit* unit);
			void removeUnit(const Coordinates& position);
			bool isUnitAt(const Coordinates& position) const;
			Unit* getUnit(const Coordinates& position);
			const std::map<Coordinates, Unit*>& getUnits() const;

			void setTerrain(const Coordinates& position, Terrain* terrain);
			void removeTerrain(const Coordinates& position);
			bool isTerrainAt(const Coordinates& position);
			Terrain* getTerrain(const Coordinates& position);
			std::map<Coordinates, Terrain*>& getTerrains();

			void setStructure(const Coordinates& position, Structure* structure);
			Structure* getStructure(const Coordinates& position) const;
			bool isStructureAt(const Coordinates& position) const;
			void removeStructureAt(const Coordinates& position);

			bool isOnBoard(Coordinates coordinates) const;

			void setWidth(unsigned int width);
			unsigned int getWidth() const { return _width; }
			void setHeight(unsigned int height);
			unsigned int getHeight() const { return _height; }

			/**
			 * @brief Call pathfinding algorithm to find path from start to end.
			 * @param start Coordinates of the start.
			 * @param end Coordinates of the end.
			 * @return Pointer to found path or nullptr if no path could be found.
			 */
			pathfinding::Path* findPath(const Coordinates& start, const Coordinates& end);

			static SID typeName;

		private:
			void resizeBackground();

			SpriteComponent* backgroundComponent_;

			std::map<Coordinates, Unit*> _units;
			std::map<Coordinates, Terrain*> _terrains;
			std::map<Coordinates, Structure*> structures_;

			unsigned int _width;
			unsigned int _height;

			BoardWorldAdapter pathfindingAdapter_;
			pathfinding::AbstractPathfinder<Coordinates>* _pathfinder;
	};
}

#endif
