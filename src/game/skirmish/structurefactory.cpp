#include "game/skirmish/structurefactory.hpp"

#include "game/skirmish/structure.hpp"

namespace qrw
{

Structure* StructureFactory::createStructure(unsigned int type)
{
	auto structure = new Structure();
	structure->setType(type);
	return structure;
}

} // namespace qrw
