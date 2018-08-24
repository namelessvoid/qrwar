#include <memory>
#include "game/skirmish/meta/coordinatemetaclass.hpp"
#include "meta/properties/tproperty.hpp"

namespace qrw
{

CoordinateMetaClass::CoordinateMetaClass(const MetaManager& metaManager)
	: MetaClass(metaManager)
{
	properties_[0] = std::make_unique<TProperty<Coordinates, int>>(&Coordinates::_x, "_x", getMetaManager());
	properties_[1] = std::make_unique<TProperty<Coordinates, int>>(&Coordinates::_y, "_y", getMetaManager());
}

void CoordinateMetaClass::serialize(const Reflectable* in, YAML::Emitter& yaml) const
{
	yaml << YAML::BeginMap;
	for(auto& property : properties_)
		property->serialize(in, yaml);
	yaml << YAML::EndMap;
}

Reflectable* CoordinateMetaClass::deserialize(const YAML::Node& yaml) const
{

	auto coordinate = new Coordinates;
	for(auto& property : properties_)
		property->deserialize(coordinate, yaml);
	return coordinate;
}

std::type_index CoordinateMetaClass::getTypeIndex() const
{
	Coordinates tmpInstance;
	return typeid(tmpInstance);
}

} // namespace qrw
