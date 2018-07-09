#ifndef QRW_STDMAPPROPERTY_HPP
#define QRW_STDMAPPROPERTY_HPP

#include <cassert>

#include "meta/metamanager.hpp"
#include "meta/metaclass.hpp"
#include "meta/properties/iproperty.hpp"

namespace qrw {

template<typename TClass, typename TKey,typename TValue>
class StdMapProperty : public IProperty
{
public:
	StdMapProperty(std::map<TKey,TValue*> TClass::* member, const std::string name)
		: IProperty(name)
	{
		member_ = member;
	}

	StdMapProperty& operator=(const StdMapProperty& rhs) = delete;

	StdMapProperty(const StdMapProperty& rhs) = delete;

	void serialize(const Reflectable* object, YAML::Emitter& out) const override
	{
		assert(dynamic_cast<const TClass*>(object)!=nullptr);

		const MetaClass* keyMetaClass = MetaManager::getMetaClassFor<TKey>();
		const MetaClass* valueMetaClass = MetaManager::getMetaClassFor<TValue>();

		const TClass* typedObject = static_cast<const TClass*>(object);
		auto binding = std::bind(StdMapProperty<TClass,TKey,TValue>::member_, typedObject);

		out << YAML::Key << getName() << YAML::Value << YAML::BeginSeq;
		for(auto iter : binding())
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

		const MetaClass* keyMetaClass = MetaManager::getMetaClassFor<TKey>();
		const MetaClass* valueMetaClass = MetaManager::getMetaClassFor<TValue>();

		TClass* typedObject = static_cast<TClass*>(object);
		auto binding = std::bind(StdMapProperty<TClass,TKey,TValue>::member_, typedObject);

		const YAML::Node& mapNode = in[getName()];
		for(YAML::const_iterator nodeIter = mapNode.begin(); nodeIter != mapNode.end(); ++nodeIter)
		{
			TKey key;
			keyMetaClass->deserialize(&key, (*nodeIter)["key"]);

			TValue* value = new TValue();
			valueMetaClass->deserialize(value, (*nodeIter)["value"]);

			binding()[key] = value;
		}
	}

private:
	std::map<TKey,TValue*> TClass::* member_;
};

} // namespace qrw

#endif // QRW_STDMAPPROPERTY_HPP
