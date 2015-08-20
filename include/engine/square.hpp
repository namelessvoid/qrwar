#ifndef QRW_SQUARE_HPP
#define QRW_SQUARE_HPP

#include "engine/coordinates.hpp"

namespace qrw
{
	class Terrain;
	class Unit;

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

			bool isAccessible();

		private:
			Terrain* _terrain;
			Unit* _unit;
			Coordinates _coordinates;
	};
}

#endif
