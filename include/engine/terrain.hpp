#ifndef QRW_TERRAIN_HPP
#define QRW_TERRAIN_HPP

#include "engine/terraintypes.hpp"

namespace qrw
{
	enum MODIFICATORS
	{
		EM_ATTACK,
		EM_DEFENSE
	};

	class Terrain
	{
		public:
			static Terrain* createTerrain(TERRAINTYPES terrainType);

			~Terrain();

			int getModificator(MODIFICATORS type);
			int* getModificators();
			TERRAINTYPES getType();

		private:
			Terrain(TERRAINTYPES _type, int attackmod, int defensemod);

			int _modificators[2];
			TERRAINTYPES _type;
	};
}

#endif
