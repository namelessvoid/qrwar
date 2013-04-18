#include "engine/terrain.hpp"

namespace qrw
{
	Terrain::Terrain(TERRAINTYPES type, int attackmod, int defensemod)
	: type(type)
	{
		modificators[EM_ATTACK] = attackmod;
		modificators[EM_DEFENSE] = defensemod;
	}

	Terrain::~Terrain()
	{
	}


}