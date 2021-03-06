#include "game/skirmish/meta/boardmetaclass.hpp"

#include "meta/metamanager.hpp"
#include "meta/properties/tproperty.hpp"
#include "meta/properties/stdmapproperty.hpp"

#include "engine/terrain.hpp"
#include "game/skirmish/structure.hpp"

#include <iostream>
#include <memory>

namespace qrw
{

BoardMetaClass::BoardMetaClass(const MetaManager& metaManager)
	: MetaClass(metaManager)
{
	properties_[0] = std::make_unique<TProperty<Board, unsigned int>>(&Board::_width, "_width", getMetaManager());
	properties_[1] = std::make_unique<TProperty<Board, unsigned int>>(&Board::_height, "_height", getMetaManager());
	properties_[2] = std::make_unique<StdMapProperty<Board, Coordinates, Terrain>>(&Board::_terrains, "_terrains", getMetaManager());
	properties_[3] = std::make_unique<StdMapProperty<Board, Coordinates, Structure>>(&Board::structures_, "structures_", getMetaManager());
}

void BoardMetaClass::serialize(const Reflectable* object, YAML::Emitter& out) const
{
	out << YAML::BeginMap;

	serializeTypeName(Board::typeName.getStringId(), out);
	for(auto& property : properties_)
		property->serialize(object, out);

	out << YAML::EndMap;
}

Reflectable* BoardMetaClass::deserialize(const YAML::Node& in) const
{
	auto board = new Board();
	for(auto& property : properties_)
		property->deserialize(board, in);
	return board;
}

} // namespace qrw




