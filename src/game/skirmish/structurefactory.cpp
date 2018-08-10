#include "game/skirmish/structurefactory.hpp"

namespace qrw
{

Structure* StructureFactory::createStructure(Structure::Type type)
{
	auto structure = new Structure();
	structure->setType(type);
	return structure;
}

} // namespace qrw
