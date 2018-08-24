#ifndef QRW_DEPLOYMENTZONEMETACLASS_HPP
#define QRW_DEPLOYMENTZONEMETACLASS_HPP

#include "meta/reflectable.hpp"
#include "meta/metaclass.hpp"

namespace qrw {

class DeploymentZoneMetaClass final : public MetaClass
{
public:
	explicit DeploymentZoneMetaClass(const MetaManager& metaManager);

	void serialize(const Reflectable* object, YAML::Emitter& out) const override;

	Reflectable* deserialize(const YAML::Node& in) const override;

    std::type_index getTypeIndex() const override;

private:
	DeploymentZoneMetaClass(const DeploymentZoneMetaClass& rhs) = delete;

	DeploymentZoneMetaClass& operator=(const DeploymentZoneMetaClass& rhs) = delete;
};


} // namespace qrw

#endif // QRW_DEPLOYMENTZONEMETACLASS_HPP
