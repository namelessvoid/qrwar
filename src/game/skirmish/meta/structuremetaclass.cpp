#include "game/skirmish/meta/structuremetaclass.hpp"

#include "meta/properties/tclassproperty.hpp"

#include "game/skirmish/structure.hpp"

namespace qrw
{

StructureMetaClass::StructureMetaClass(const MetaManager& metaManager)
	: MetaClass(metaManager)
{
	properties_[0] = std::make_unique<TClassProperty<Structure,Coordinates>>(&Structure::position_, "position_", metaManager);
}

void StructureMetaClass::serialize(const Reflectable* object, YAML::Emitter& out) const
{
	out << YAML::BeginMap;
	properties_[0]->serialize(object, out);
	out << YAML::EndMap;
}

void StructureMetaClass::deserialize(Reflectable* object, const YAML::Node& in) const
{
	properties_[0]->deserialize(object, in);
}

std::type_index StructureMetaClass::getTypeIndex() const
{
	return typeid(Structure);
}

} // namespace qrw
