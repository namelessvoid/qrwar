#ifndef QRW_METACLASS_HPP
#define QRW_METACLASS_HPP

#include <yaml-cpp/yaml.h>

#include <typeindex>

namespace qrw {

class MetaClass
{
public:
    MetaClass();

    virtual ~MetaClass();

    virtual void serialze(YAML::Emitter& out) = 0;

    virtual std::type_index getTypeIndex() const = 0;

private:
    MetaClass(const MetaClass& rhs) = delete;

    MetaClass& operator=(const MetaClass& rhs) = delete;
};

} // namespace qrw

#endif // QRW_METACLASS_HPP
