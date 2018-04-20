#ifndef QRW_DEPLOYMENTZONEMETACLASS_HPP
#define QRW_DEPLOYMENTZONEMETACLASS_HPP

#include "meta/metaclass.hpp"

namespace qrw {

class DeploymentZoneMetaClass final : public MetaClass
{
public:
	DeploymentZoneMetaClass();

	virtual ~DeploymentZoneMetaClass();

	virtual void serialize(const GameObject* object, YAML::Emitter& out) const;

	virtual GameObject* deserialize(const YAML::Node& in) const;

    virtual std::type_index getTypeIndex() const;

private:
	DeploymentZoneMetaClass(const DeploymentZoneMetaClass& rhs) = delete;

	DeploymentZoneMetaClass& operator=(const DeploymentZoneMetaClass& rhs) = delete;
};


} // namespace qrw

#endif // QRW_DEPLOYMENTZONEMETACLASS_HPP