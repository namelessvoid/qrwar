#include "game/meta/coordinatemetaclass.hpp"
#include "meta/properties/tproperty.hpp"

namespace qrw
{

CoordinateMetaClass::CoordinateMetaClass()
{
	properties_[0].reset(new TProperty<Coordinates,int>(&Coordinates::_x, "_x"));
	properties_[1].reset(new TProperty<Coordinates,int>(&Coordinates::_y, "_y"));
}

void CoordinateMetaClass::serialize(const Reflectable* in, YAML::Emitter& yaml) const
{
	yaml << YAML::BeginMap;
	for(auto& property : properties_)
		property->serialize(in, yaml);
	yaml << YAML::EndMap;
}

void CoordinateMetaClass::deserialize(Reflectable* out, const YAML::Node& yaml) const
{
	assert(dynamic_cast<Coordinates*>(out)!=nullptr);

	for(auto& property : properties_)
		property->deserialize(out, yaml);
}

std::type_index CoordinateMetaClass::getTypeIndex() const
{
	Coordinates tmpInstance;
	return typeid(tmpInstance);
}

} // namespace qrw
