#include "meta/metaclass.hpp"

#include "meta/metamanager.hpp"

namespace qrw
{

const std::string MetaClass::TYPE_NAME_YAML_KEY = "$type";

MetaClass::MetaClass(const MetaManager& metaManager)
	: metaManager_(metaManager)
{
}

void MetaClass::serializeTypeName(const std::string& typeName, YAML::Emitter& out) const
{
	out << YAML::Key << TYPE_NAME_YAML_KEY << YAML::Value << typeName;
}

} // namespace qrw
