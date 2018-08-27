#ifndef QRW_METACLASS_HPP
#define QRW_METACLASS_HPP

#include <yaml-cpp/yaml.h>

#include <typeindex>
#include "reflectable.hpp"

namespace qrw {

class MetaManager;

class MetaClass
{
public:
	const static std::string TYPE_NAME_YAML_KEY;

    MetaClass(const MetaManager& metaManager);

    virtual ~MetaClass() = default;

	virtual void serialize(const Reflectable* object, YAML::Emitter& out) const = 0;
	void serializeTypeName(const std::string& typeName, YAML::Emitter& out) const;

	//virtual const std::string& getTypeName() = 0;
	//virtual std::type_index getTypeIndex() const = 0;

	virtual Reflectable* deserialize(const YAML::Node& in) const = 0;

    const MetaManager& getMetaManager() const { return metaManager_; }

private:
    MetaClass(const MetaClass& rhs) = delete;

    MetaClass& operator=(const MetaClass& rhs) = delete;

    const MetaManager& metaManager_;
};

} // namespace qrw

#endif // QRW_METACLASS_HPP
