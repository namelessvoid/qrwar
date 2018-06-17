#ifndef QRW_COORDINATEMETACLASS_HPP
#define QRW_COORDINATEMETACLASS_HPP

#include <array>

#include "meta/metaclass.hpp"
#include "meta/properties/iproperty.hpp"

#include "engine/coordinates.hpp"

namespace qrw {

class CoordinateMetaClass : public MetaClass
{
public:
	CoordinateMetaClass();

	~CoordinateMetaClass() override = default;

	void serialize(const Reflectable* in, YAML::Emitter& yaml) const override;

	void deserialize(Reflectable* gameObject, const YAML::Node& yaml) const override;

	std::type_index getTypeIndex() const override;

	CoordinateMetaClass(const CoordinateMetaClass& rhs) = delete;
	CoordinateMetaClass& operator=(const CoordinateMetaClass& rhs) = delete;

private:
	std::array<std::unique_ptr<IProperty>,2> properties_;
};


} // namespace qrw

#endif // QRW_COORDINATEMETACLASS_HPP
