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
    MetaClass(const MetaManager& metaManager);

    virtual ~MetaClass();

	virtual void serialize(const Reflectable* object, YAML::Emitter& out) const = 0;

	virtual Reflectable* deserialize(const YAML::Node& in) const = 0;

    virtual std::type_index getTypeIndex() const = 0;

    const MetaManager& getMetaManager() const { return metaManager_; }

private:
    MetaClass(const MetaClass& rhs) = delete;

    MetaClass& operator=(const MetaClass& rhs) = delete;

    const MetaManager& metaManager_;
};

} // namespace qrw

#endif // QRW_METACLASS_HPP
