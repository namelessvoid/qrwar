#ifndef QRW_STRUCTUREMETACLASS_HPP
#define QRW_STRUCTUREMETACLASS_HPP

#include <foundation/gameobject.hpp>
#include "meta/metaclass.hpp"
#include "meta/properties/iproperty.hpp"

namespace qrw
{

class StructureMetaClass : public MetaClass
{
public:
	StructureMetaClass(const MetaManager& metaManager);

	void serialize(const Reflectable* object, YAML::Emitter& out) const override;

	Reflectable* deserialize(const YAML::Node& in) const override;

private:
	std::array<std::unique_ptr<IProperty>,2> properties_;
};

} // namespace qrw

#endif //QRW_STRUCTUREMETACLASS_HPP
