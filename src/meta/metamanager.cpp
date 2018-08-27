#include "meta/metamanager.hpp"

namespace qrw
{

Reflectable* MetaManager::deserialize(YAML::Node node) const
{
	assert(node[MetaClass::TYPE_NAME_YAML_KEY]);
	auto metaClass = getMetaClassByTypeName(node[MetaClass::TYPE_NAME_YAML_KEY].as<std::string>());
	return metaClass->deserialize(node);
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
