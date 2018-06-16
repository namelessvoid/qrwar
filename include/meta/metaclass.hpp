#ifndef QRW_METACLASS_HPP
#define QRW_METACLASS_HPP

#include <yaml-cpp/yaml.h>

#include <typeindex>
#include "reflectable.hpp"

namespace qrw {

class GameObject;

class MetaClass
{
public:
    MetaClass();

    virtual ~MetaClass();

	virtual void serialize(const Reflectable* object, YAML::Emitter& out) const = 0;

	virtual void deserialize(Reflectable* gameObject, const YAML::Node& in) const = 0;

    virtual std::type_index getTypeIndex() const = 0;

private:
    MetaClass(const MetaClass& rhs) = delete;

    MetaClass& operator=(const MetaClass& rhs) = delete;
};

} // namespace qrw

#endif // QRW_METACLASS_HPP
