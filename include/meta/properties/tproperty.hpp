#ifndef QRW_TPROPERTY_HPP
#define QRW_TPROPERTY_HPP

#include <cassert>
#include <yaml-cpp/yaml.h>
#include <functional>

#include "meta/properties/iproperty.hpp"

namespace qrw {

template<typename TClassType, typename TPropertyType>
class TProperty : public IProperty
{
public:
	TProperty(TPropertyType TClassType::*member, const std::string& name, const MetaManager& metaManager)
		: IProperty(name, metaManager)
	{
		member_ = member;
	}

	TProperty(const TProperty& rhs) = delete;

	TProperty& operator=(const TProperty& rhs) = delete;

	void serialize(const Reflectable* object, YAML::Emitter& out) const override
	{
		assert(dynamic_cast<const TClassType*>(object)!=nullptr);
		auto typedObject = static_cast<const TClassType*>(object);
		auto binding = std::bind(TProperty<TClassType,TPropertyType>::member_, typedObject);

		out << YAML::Key << getName() << YAML::Value;
		serializeInternal(binding(), out);
	}

	void deserialize(Reflectable* object, const YAML::Node& in) const override
	{
		assert(dynamic_cast<TClassType*>(object)!=nullptr);

		TClassType* typedObject = static_cast<TClassType*>(object);
		auto binding = std::bind(TProperty<TClassType,TPropertyType>::member_, typedObject);
		binding() = deserializeInternal(in[getName()]);
	};

private:
	template <typename TValue = TPropertyType>
	typename std::enable_if<!std::is_enum<TValue>::value>::type
	serializeInternal(const TValue value, YAML::Emitter& out) const
	{
		out << value;
	}

	template<typename TValue = TPropertyType>
	typename std::enable_if<std::is_enum<TValue>::value>::type
	serializeInternal(const TValue value, YAML::Emitter& out) const
	{
		out << static_cast<int>(value);
	};

	template <typename TValue = TPropertyType>
	typename std::enable_if<!std::is_enum<TValue>::value,TValue>::type
	deserializeInternal(const YAML::Node& node) const
	{
		return node.as<TValue>();
	}

	template<typename TValue = TPropertyType>
	typename std::enable_if<std::is_enum<TValue>::value,TValue>::type
	deserializeInternal(const YAML::Node& node) const
	{
		return static_cast<TValue>(node.as<int>());
	};

	TPropertyType TClassType::* member_;
};

} // namespace qrw

#endif // QRW_TPROPERTY_HPP
