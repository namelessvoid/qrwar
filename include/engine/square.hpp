#ifndef QRW_SQUARE_HPP
#define QRW_SQUARE_HPP

#include "engine/coordinates.hpp"
#include "engine/terrain.hpp"

namespace qrw
{
	class Terrain;
	class Unit;

	class Square
	{
		public:
			Square(int x, int y);
			~Square();

			void setTerrain(Terrain::Ptr terrain);
			Terrain::Ptr getTerrain();

			void setUnit(Unit* unit);
			Unit* getUnit();

			int getDistance(Square* suqare);

			const Coordinates& getCoordinates() const;
			int getXPosition();
			int getYPosition();

			bool isAccessible();

		private:
			Terrain::Ptr _terrain;
			Unit* _unit;
			Coordinates _coordinates;
	};
}

#endif
