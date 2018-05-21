#ifndef QRW_TPROPERTY_HPP
#define QRW_TPROPERTY_HPP

#include "meta/properties/iproperty.hpp"

namespace qrw {

template<typename TClassType, typename TPropertyType>
class TProperty : public IProperty
{
public:
	TProperty(TPropertyType TClassType::*member, const std::string& name)
		: IProperty(name)
	{
		member_ = member;
	}

	virtual void serialize(const Reflectable* object, YAML::Emitter& out) const
	{
		assert(dynamic_cast<const TClassType*>(object)!=nullptr);

		const TClassType* typedObject = static_cast<const TClassType*>(object);
		auto binding = std::bind(TProperty<TClassType,TPropertyType>::member_, typedObject);
		out << YAML::Key << getName() << YAML::Value << binding();
	}

	virtual void deserialize(Reflectable* object, const YAML::Node& in) const
	{
		
	};

private:
	TProperty(const TProperty& rhs) = delete;

	TProperty& operator=(const TProperty& rhs) = delete;

	TPropertyType TClassType::* member_;
};

} // namespace qrw

#endif // QRW_TPROPERTY_HPP
