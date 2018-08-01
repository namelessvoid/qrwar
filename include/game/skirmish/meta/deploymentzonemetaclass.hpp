#ifndef QRW_DEPLOYMENTZONEMETACLASS_HPP
#define QRW_DEPLOYMENTZONEMETACLASS_HPP

#include "meta/reflectable.hpp"
#include "meta/metaclass.hpp"

namespace qrw {

class DeploymentZoneMetaClass final : public MetaClass
{
public:
	DeploymentZoneMetaClass(const MetaManager& metaManager);

	virtual ~DeploymentZoneMetaClass();

	virtual void serialize(const Reflectable* object, YAML::Emitter& out) const;

	virtual void deserialize(Reflectable* gameObject, const YAML::Node& in) const;

    virtual std::type_index getTypeIndex() const;

private:
	DeploymentZoneMetaClass(const DeploymentZoneMetaClass& rhs) = delete;

	DeploymentZoneMetaClass& operator=(const DeploymentZoneMetaClass& rhs) = delete;
};


} // namespace qrw

#endif // QRW_DEPLOYMENTZONEMETACLASS_HPP
