#include "engine/terrain.hpp"

namespace qrw
{
	Terrain::Terrain(TERRAINTYPES type, int attackmod, int defensemod)
	: _type(type)
	{
		_modificators[EM_ATTACK] = attackmod;
		_modificators[EM_DEFENSE] = defensemod;
	}

	Terrain::~Terrain()
	{
	}
}
