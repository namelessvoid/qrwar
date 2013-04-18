#ifndef QRW_TERRAIN_HPP
#define QRW_TERRAIN_HPP

namespace qrw
{
	enum MODIFICATORS
	{
		EM_ATTACK,
		EM_DEFENSE
	};

	enum TERRAINTYPES
	{
		ET_WOOD,
		ET_HILL,

	};

	class Terrain
	{
		public:
			Terrain(TERRAINTYPES type, int attackmod, int defensemod);
			~Terrain();

			inline int getModificator(MODIFICATORS type)
				{ return modificators[type]; };
			inline TERRAINTYPES getType() { return type; };

		private:
			int modificators[2];
			TERRAINTYPES type;
	};
}

#endif