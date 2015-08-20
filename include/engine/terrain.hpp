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
			Terrain(TERRAINTYPES _type, int attackmod, int defensemod);
			~Terrain();

			inline int getModificator(MODIFICATORS type)
				{ return _modificators[type]; };
			inline int* getModificators()
				{ return _modificators; }
			inline TERRAINTYPES getType() { return _type; };

		private:
			int _modificators[2];
			TERRAINTYPES _type;
	};
}

#endif
