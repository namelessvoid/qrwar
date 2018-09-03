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
	ValueStub value1(11), value2(22);
	reflectableStub.mapProperty[key1] = &value1;
	reflectableStub.mapProperty[key2] = &value2;

	// Act
	out << YAML::BeginMap;
	stdMapProperty.serialize(&reflectableStub, out);
	out << YAML::EndMap;

	// Assert Result
	YAML::Node result = YAML::Load(out.c_str());
	ASSERT_TRUE(result["mapProperty"]) << "Key 'mapProperty' does not exist";
	ASSERT_EQ(result["mapProperty"].size(), 2);
	ASSERT_TRUE(result["mapProperty"][0]) << "'mapProperty' should be an array";

	ASSERT_TRUE(result["mapProperty"][0]["key"]["id"])   << "Key 'mapProperty.0.key.id' does not exist";
	ASSERT_TRUE(result["mapProperty"][0]["value"]["id"]) << "Key 'mapProperty.0.value.id' does not exist";
	EXPECT_EQ(result["mapProperty"][0]["key"]["id"].as<int>(), 1);
	EXPECT_EQ(result["mapProperty"][0]["value"]["id"].as<int>(), 11);

	ASSERT_TRUE(result["mapProperty"][1]) << "'mapProperty' should be an array";
	ASSERT_TRUE(result["mapProperty"][1]["key"]["id"])   << "Key 'mapProperty.1.key.id' does not exist";
	ASSERT_TRUE(result["mapProperty"][1]["value"]["id"]) << "Key 'mapProperty.1.value.id' does not exist";
	EXPECT_EQ(result["mapProperty"][1]["key"]["id"].as<int>(), 2);
	EXPECT_EQ(result["mapProperty"][1]["value"]["id"].as<int>(), 22);
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