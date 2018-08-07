#include "game/skirmish/structurefactory.hpp"

#include "game/skirmish/structure.hpp"

namespace qrw
{

Structure* StructureFactory::createStructure(int type)
{
	return new Structure();
}

} // namespace qrw
