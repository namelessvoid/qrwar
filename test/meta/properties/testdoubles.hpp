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

	ValueStub(int id = 0) : id(id) {}
	ValueStub& operator=(const ValueStub& rhs) = default;
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

	MOCK_CONST_METHOD2(serialize, void(const qrw::Reflectable* object, YAML::Emitter& out));
	MOCK_CONST_METHOD1(deserialize, qrw::Reflectable*(const YAML::Node& in));
};

class ValueStubMetaClass : public qrw::MetaClass
{
public:
	ValueStubMetaClass(const qrw::MetaManager& metaManager) : MetaClass(metaManager) {}

	MOCK_CONST_METHOD2(serialize, void(const qrw::Reflectable* object, YAML::Emitter& out));
	MOCK_CONST_METHOD1(deserialize, qrw::Reflectable*(const YAML::Node& in));
};

ACTION_P(SerializeToYaml, scalar) { arg1 << scalar; }

#endif //TESTDOUBLES_HPP
