#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "meta/properties/stdmapproperty.hpp"

#include "testdoubles.hpp"

using ::testing::_;
using ::testing::Eq;
using ::testing::Field;
using ::testing::WhenDynamicCastTo;
using ::testing::Invoke;

TEST(StdMapProperty_Serialize, Then_yaml_contains_keys_and_values)
{
	// Arrange
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<KeyMetaClassMock>(KeyStub::typeName);
	metaManager.registerMetaClass<ValueStubMetaClass>(ValueStub::typeName);

	qrw::StdMapProperty<ReflectableStub,KeyStub,ValueStub> stdMapProperty(&ReflectableStub::mapProperty, "mapProperty", metaManager);
	YAML::Emitter out;

	ReflectableStub reflectableStub;
	KeyStub key1(1), key2(2);
	ValueStub value1, value2;
	reflectableStub.mapProperty[key1] = &value1;
	reflectableStub.mapProperty[key2] = &value2;

	// Assert Mocks
	auto keyMetaClassMock = static_cast<const KeyMetaClassMock*>(metaManager.getMetaClassFor<KeyStub>());
	EXPECT_CALL(*keyMetaClassMock, serialize(WhenDynamicCastTo<const KeyStub*>(Field(&KeyStub::id, Eq(1))), _))
			.WillOnce(SerializeToYaml("firstKey"));
	EXPECT_CALL(*keyMetaClassMock, serialize(WhenDynamicCastTo<const KeyStub*>(Field(&KeyStub::id, Eq(2))), _))
			.WillOnce(SerializeToYaml("secondKey"));

	auto valueStubMetaClass = static_cast<const ValueStubMetaClass*>(metaManager.getMetaClassFor<ValueStub>());
	EXPECT_CALL(*valueStubMetaClass, serialize(&value1, _))
			.WillOnce(SerializeToYaml("firstValue"));
	EXPECT_CALL(*valueStubMetaClass, serialize(&value2, _))
			.WillOnce(SerializeToYaml("secondValue"));

	// Act
	out << YAML::BeginMap;
	stdMapProperty.serialize(&reflectableStub, out);
	out << YAML::EndMap;

	// Assert Result
	YAML::Node result = YAML::Load(out.c_str());
	ASSERT_TRUE(result["mapProperty"]) << "Key 'mapProperty' does not exist";
	ASSERT_EQ(result["mapProperty"].size(), 2);
	ASSERT_TRUE(result["mapProperty"][0]) << "'mapProperty' should be an array";

	ASSERT_TRUE(result["mapProperty"][0]["key"])   << "Key 'mapProperty.0.key' does not exist";
	ASSERT_TRUE(result["mapProperty"][0]["value"]) << "Key 'mapProperty.0.value' does not exist";
	EXPECT_EQ(result["mapProperty"][0]["key"].as<std::string>(), "firstKey");
	EXPECT_EQ(result["mapProperty"][0]["value"].as<std::string>(), "firstValue");

	ASSERT_TRUE(result["mapProperty"][1]) << "'mapProperty' should be an array";
	ASSERT_TRUE(result["mapProperty"][1]["key"])   << "Key 'mapProperty.1.key' does not exist";
	ASSERT_TRUE(result["mapProperty"][1]["value"]) << "Key 'mapProperty.1.value' does not exist";
	EXPECT_EQ(result["mapProperty"][1]["key"].as<std::string>(), "secondKey");
	EXPECT_EQ(result["mapProperty"][1]["value"].as<std::string>(), "secondValue");
}

TEST(StdMapProperty_Serialize, If_property_is_empty_Then_yaml_node_is_empty)
{
	// Arrange
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<KeyMetaClassMock>(KeyStub::typeName);
	metaManager.registerMetaClass<ValueStubMetaClass>(ValueStub::typeName);

	qrw::StdMapProperty<ReflectableStub,KeyStub,ValueStub> stdMapProperty(&ReflectableStub::mapProperty, "mapProperty", metaManager);

	YAML::Emitter out;

	ReflectableStub reflectableStub;

	// Act
	out << YAML::BeginMap;
	stdMapProperty.serialize(&reflectableStub, out);
	out << YAML::EndMap;

	// Assert
	YAML::Node result = YAML::Load(out.c_str());
	ASSERT_TRUE(result["mapProperty"]) << "Key 'mapProperty' does not exist";
	EXPECT_EQ(result["mapProperty"].size(), 0);
}