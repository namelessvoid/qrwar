#ifndef QRW_SQUARE_HPP
#define QRW_SQUARE_HPP

#include "engine/terrain.hpp"
#include "engine/unit.hpp"
#include "engine/coordinates.hpp"

namespace qrw
{
	class Square
	{
		public:
			Square(int x, int y);
			~Square();

			void setTerrain(Terrain* terrain);
			Terrain* getTerrain();

			void setUnit(Unit* unit);
			Unit* getUnit();

			int getDistance(Square* suqare);

			const Coordinates& getCoordinates() const;
			int getXPosition();
			int getYPosition();

		private:
			Terrain* terrain;
			Unit* unit;
			Coordinates coordinates;
	};
}

#endif