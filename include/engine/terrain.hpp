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
			Terrain(TERRAINTYPES type, int attackmod, int defensemod);
			~Terrain();

			inline int getModificator(MODIFICATORS type)
				{ return modificators[type]; };
			inline int* getModificators()
				{ return modificators; }
			inline TERRAINTYPES getType() { return type; };

		private:
			int modificators[2];
			TERRAINTYPES type;
	};
}

#endif
