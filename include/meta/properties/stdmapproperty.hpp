#ifndef QRW_STDMAPPROPERTY_HPP
#define QRW_STDMAPPROPERTY_HPP

#include <cassert>

#include "meta/metamanager.hpp"
#include "meta/metaclass.hpp"
#include "meta/properties/iproperty.hpp"

namespace qrw {

/// Serializes an std::map<TKey,TValue> within class TClass.
/// Note: TKey must be a non-pointer/non-reference type  and TValue must be a pointer type
template<typename TClass, typename TKey,typename TValue>
class StdMapProperty : public IProperty
{
public:
	StdMapProperty(std::map<TKey,TValue*> TClass::* member, const std::string name, const MetaManager& metaManager)
		: IProperty(name, metaManager)
	{
		member_ = member;
	}

	StdMapProperty& operator=(const StdMapProperty& rhs) = delete;

	StdMapProperty(const StdMapProperty& rhs) = delete;

	void serialize(const Reflectable* object, YAML::Emitter& out) const override
	{
		assert(dynamic_cast<const TClass*>(object)!=nullptr);

		const MetaClass* keyMetaClass = getMetaManager().getMetaClassFor<TKey>();
		const MetaClass* valueMetaClass = getMetaManager().getMetaClassFor<TValue>();

		const TClass* typedObject = static_cast<const TClass*>(object);
		auto binding = std::bind(StdMapProperty<TClass,TKey,TValue>::member_, typedObject);

		out << YAML::Key << getName() << YAML::Value << YAML::BeginSeq;
		for(auto& iter : binding())
		{
			out << YAML::BeginMap;
				out << YAML::Key << "key" << YAML::Value;
				keyMetaClass->serialize(&iter.first, out);

				out << YAML::Key << "value" << YAML::Value;
				valueMetaClass->serialize(iter.second, out);
			out << YAML::EndMap;
		}
		out << YAML::EndSeq;
	}

	void deserialize(Reflectable* object, const YAML::Node& in) const override
	{
		assert(dynamic_cast<TClass*>(object)!=nullptr);

		const MetaClass* keyMetaClass = getMetaManager().getMetaClassFor<TKey>();
		const MetaClass* valueMetaClass = getMetaManager().getMetaClassFor<TValue>();

		TClass* typedObject = static_cast<TClass*>(object);
		auto binding = std::bind(StdMapProperty<TClass,TKey,TValue>::member_, typedObject);

		const YAML::Node& mapNode = in[getName()];
		for(YAML::const_iterator nodeIter = mapNode.begin(); nodeIter != mapNode.end(); ++nodeIter)
		{
			TKey* key = static_cast<TKey*>(keyMetaClass->deserialize((*nodeIter)["key"]));
			TValue* value = static_cast<TValue*>(valueMetaClass->deserialize((*nodeIter)["value"]));

			binding()[*key] = value;

			delete key;
		}
	}

private:
	std::map<TKey,TValue*> TClass::* member_;
};

} // namespace qrw

#endif // QRW_STDMAPPROPERTY_HPP
