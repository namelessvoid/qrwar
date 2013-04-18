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

		private:
			Terrain* terrain;
			Unit* unit;
	};
}

#endif