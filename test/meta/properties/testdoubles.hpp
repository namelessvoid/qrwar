#ifndef TESTDOUBLES_HPP
#define TESTDOUBLES_HPP

#include <gmock/gmock.h>

#include "meta/metamanager.hpp"
#include "meta/reflectable.hpp"
#include "core/sid.hpp"

class KeyStub : public qrw::Reflectable
{
public:
	KeyStub(int id = 0) : id(id) {}
	KeyStub(const KeyStub& rhs) { id = rhs.id; }

	static qrw::SID typeName;
	int id;

	bool operator<(const KeyStub& rhs) const { return this->id < rhs.id; }
};

class ValueStub : public qrw::Reflectable
{
public:
	static qrw::SID typeName;
	int id;
};

class ReflectableStub : public qrw::Reflectable
{
public:
	ValueStub classProperty;
	std::map<KeyStub,ValueStub*> mapProperty;

	enum class EnumType { ZERO = 0, ONE = 1 } enumProperty;
};

class KeyMetaClassMock : public qrw::MetaClass
{
public:
	KeyMetaClassMock(qrw::MetaManager& metaManager) : qrw::MetaClass(metaManager) {}

	MOCK_CONST_METHOD2(serialize, void(const qrw::Reflectable*, YAML::Emitter&));
	MOCK_CONST_METHOD2(deserialize, void(qrw::Reflectable*, const YAML::Node&));
	MOCK_CONST_METHOD0(getTypeIndex, std::type_index());
};

class ValueStubMetaClass : public qrw::MetaClass
{
public:
	ValueStubMetaClass(const qrw::MetaManager& metaManager) : MetaClass(metaManager) {}

	MOCK_CONST_METHOD2(serialize, void(const qrw::Reflectable* object, YAML::Emitter& out));
	MOCK_CONST_METHOD2(deserialize, void(qrw::Reflectable* object, const YAML::Node& in));
	MOCK_CONST_METHOD0(getTypeIndex, std::type_index());
};

ACTION_P(SerializeToYaml, scalar) { arg1 << scalar; }
ACTION_P(DeserializeKey, id) { dynamic_cast<KeyStub*>(arg0)->id = id; }
ACTION_P(DeserializeValue, id) { dynamic_cast<ValueStub*>(arg0)->id = id; }

#endif //TESTDOUBLES_HPP
