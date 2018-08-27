#include "meta/metamanager.hpp"

namespace qrw
{

Reflectable* MetaManager::deserialize(YAML::Node node) const
{
	throw "Not implemented";

	assert(node["type"]);
	auto metaClass = getMetaClassByTypeName(node["type"].as<std::string>());
}

MetaClass* MetaManager::getMetaClassByTypeName(const std::string& typeName) const
{
	assert(metaClasses_.find(typeName) != metaClasses_.end());
	return metaClasses_.find(typeName)->second.get();
}

void MetaManager::serialize(const Reflectable* reflectable, YAML::Emitter& out) const
{
	assert(metaClasses_.find(reflectable->getTypeName()) != metaClasses_.end());

	MetaClass* metaClass = metaClasses_.find(reflectable->getTypeName())->second.get();
	metaClass->serialize(reflectable, out);
}


} // namespace qrw
