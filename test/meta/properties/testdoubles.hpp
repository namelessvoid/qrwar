#ifndef TESTDOUBLES_HPP
#define TESTDOUBLES_HPP

#include <gmock/gmock.h>

#include "meta/metamanager.hpp"
#include "meta/reflectable.hpp"
#include "core/sid.hpp"

class KeyStub : public qrw::Reflectable
{
public:
	static qrw::SID typeName;
	const qrw::SID& getTypeName() const override { return typeName; }

	KeyStub(int id = 0) : id(id) {}
	KeyStub(const KeyStub& rhs) { id = rhs.id; }

	int id;

	bool operator<(const KeyStub& rhs) const { return this->id < rhs.id; }
};

class ValueStub : public qrw::Reflectable
{
public:
	static qrw::SID typeName;
	const qrw::SID& getTypeName() const override { return typeName; }

	int id;

	ValueStub(int id = 0) : id(id) {}
	ValueStub& operator=(const ValueStub& rhs) = default;
};

class ReflectableStub : public qrw::Reflectable
{
public:
	static qrw::SID typeName;
	const qrw::SID& getTypeName() const override { return typeName; }

	ValueStub classProperty;
	std::map<KeyStub,ValueStub*> mapProperty;

	enum class EnumType { ZERO = 0, ONE = 1 } enumProperty;
};

class KeyMetaClassMock : public qrw::MetaClass
{
public:
	KeyMetaClassMock(qrw::MetaManager& metaManager) : qrw::MetaClass(metaManager) {}

	void serialize(const qrw::Reflectable* object, YAML::Emitter& out) const override
	{
		out << YAML::BeginMap
				<< YAML::Key << qrw::MetaClass::TYPE_NAME_YAML_KEY << YAML::Value << object->getTypeName().getStringId()
				<< YAML::Key << "id" << YAML::Value << dynamic_cast<const KeyStub*>(object)->id
			<< YAML::EndMap;
	}

	qrw::Reflectable* deserialize(const YAML::Node& in) const override
	{
		return new KeyStub(in["id"].as<int>());
	}


};

class ValueStubMetaClass : public qrw::MetaClass
{
public:
	ValueStubMetaClass(const qrw::MetaManager& metaManager) : MetaClass(metaManager) {}

	void serialize(const qrw::Reflectable* object, YAML::Emitter& out) const override
	{
		out << YAML::BeginMap
			<< YAML::Key << qrw::MetaClass::TYPE_NAME_YAML_KEY << YAML::Value << object->getTypeName().getStringId()
			<< YAML::Key << "id" << YAML::Value << dynamic_cast<const ValueStub*>(object)->id
			<< YAML::EndMap;
	}

	qrw::Reflectable* deserialize(const YAML::Node& in) const override
	{
		return new ValueStub(in["id"].as<int>());
	}

};

ACTION_P(SerializeToYaml, scalar) { arg1 << scalar; }

#endif //TESTDOUBLES_HPP
