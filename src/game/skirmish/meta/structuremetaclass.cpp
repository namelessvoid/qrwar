#include "game/skirmish/meta/structuremetaclass.hpp"

#include <memory>

#include "meta/properties/tclassproperty.hpp"
#include "meta/properties/tproperty.hpp"

#include "game/skirmish/structure.hpp"

namespace qrw
{

StructureMetaClass::StructureMetaClass(const MetaManager& metaManager)
	: MetaClass(metaManager)
{
	properties_[0] = std::make_unique<TClassProperty<Structure,Coordinates>>(&Structure::position_, "position_", metaManager);
	properties_[1] = std::make_unique<TProperty<Structure,Structure::Type>>(&Structure::type_, "type_", metaManager);
}

void StructureMetaClass::serialize(const Reflectable* object, YAML::Emitter& out) const
{
	out << YAML::BeginMap;
	serializeTypeName(Structure::typeName.getStringId(), out);
	for(auto& property : properties_)
		property->serialize(object, out);
	out << YAML::EndMap;
}

Reflectable* StructureMetaClass::deserialize(const YAML::Node& in) const
{
	auto structure = new Structure();
	for(auto& property : properties_)
		property->deserialize(structure, in);
	return structure;
}

} // namespace qrw
