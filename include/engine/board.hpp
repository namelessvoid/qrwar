#ifndef QRW_BOARD_HPP
#define QRW_BOARD_HPP

#include <memory>
#include <map>

#include <SFML/System/Vector2.hpp>

#include "foundation/gameobject.hpp"

namespace qrw
{

namespace pathfinding
{
class AbstractPathfinder;
class Path;
}

	class Coordinates;
	class Unit;
	class Terrain;
	class SpriteComponent;

	class Board : public GameObject
	{
		public:
			Board()
				: Board(0, 0)
			{}

			Board(unsigned int width, unsigned int height);
			~Board();

			void setUnit(const Coordinates& position, Unit* unit);
			void removeUnit(const Coordinates& position);
			bool isUnitAt(const Coordinates& position);
			Unit* getUnit(const Coordinates& position);
			const std::map<Coordinates, Unit*>& getUnits() const;

			void setTerrain(const Coordinates& position, Terrain* terrain);
			void removeTerrain(const Coordinates& position);
			bool isTerrainAt(const Coordinates& position);
			Terrain* getTerrain(const Coordinates& position);
			const std::map<Coordinates, Terrain*>& getTerrains() const;

			bool isOnBoard(Coordinates coordinates);

			void setWidth(unsigned int width);
			void setHeight(unsigned int height);

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

			unsigned int _width;
			unsigned int _height;

			pathfinding::AbstractPathfinder* _pathfinder;
	};
}

#endif
