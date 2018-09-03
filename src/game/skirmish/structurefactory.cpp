#include "game/skirmish/structurefactory.hpp"

#include "game/skirmish/wall.hpp"
#include "game/skirmish/stairs.hpp"

namespace qrw
{

Structure* StructureFactory::createStructure(Structure::Type type)
{
	switch(type)
	{
		case Structure::Type::WALL:
			return new Wall();
		case Structure::Type::STAIRS:
			return new Stairs();
	}

	return nullptr;
}

} // namespace qrw
