#ifndef QRW_SQUARE_HPP
#define QRW_SQUARE_HPP

#include "engine/terrain.hpp"
#include "engine/unit.hpp"

namespace qrw
{
	class Square
	{
		public:
			Square();
			~Square();

			void setTerrain(Terrain* terrain);
			Terrain* getTerrain();

			void setUnit(Unit* unit);
			Unit* getUnit();

			void setPosition(int x, int y);
			int getDistance(Square* suqare);
			int getXPosition();
			int getYPosition();

		private:
			Terrain* terrain;
			Unit* unit;
			int xpos, ypos;
	};
}

#endif