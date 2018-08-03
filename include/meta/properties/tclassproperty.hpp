#ifndef QRW_TCLASSPROPERTY_HPP
#define QRW_TCLASSPROPERTY_HPP

#include <cassert>
#include <functional>

#include <yaml-cpp/yaml.h>

#include "iproperty.hpp"
#include "meta/metamanager.hpp"

namespace qrw
{

template<class TClass, class TPropertyClass>
class TClassProperty : public IProperty
{
public:
	explicit TClassProperty(TPropertyClass TClass::*member, const std::string& name, const MetaManager& metaManager)
		: IProperty(name, metaManager),
		  member_(member)
	{
	}

	void serialize(const Reflectable* object, YAML::Emitter& out) const override
	{
		assert(dynamic_cast<const TClass*>(object));

		auto typedObject = static_cast<const TClass*>(object);
		auto binding = std::bind(TClassProperty<TClass,TPropertyClass>::member_, typedObject);

		auto metaClass = getMetaManager().getMetaClassFor<TPropertyClass>();

		out << YAML::Key << getName() << YAML::Value;
		metaClass->serialize(&binding(), out);
	}

	void deserialize(Reflectable* object, const YAML::Node& in) const override
	{
		assert(dynamic_cast<TClass*>(object));

		auto typedObject = static_cast<TClass*>(object);
		auto binding = std::bind(TClassProperty<TClass,TPropertyClass>::member_, typedObject);

		auto metaClass = getMetaManager().getMetaClassFor<TPropertyClass>();

		metaClass->deserialize(&binding(), in[getName()]);
	}

private:
	TPropertyClass TClass::* member_;
};

} // namespace qrw

#endif //QRW_TCLASSPROPERTY_HPP
