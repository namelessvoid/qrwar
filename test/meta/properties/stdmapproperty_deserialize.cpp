#include <gtest/gtest.h>
#include <meta/properties/stdmapproperty.hpp>

#include "testdoubles.hpp"

using testing::_;
using testing::WhenDynamicCastTo;
using testing::IsEmpty;
using testing::Property;
using testing::Return;

TEST(StdMapProperty_Deserialize, Then_key_and_value_are_deserialized)
{
	// Arrange
	YAML::Node node;
	node["mapProperty"][0]["key"]["id"] = 1;
	node["mapProperty"][0]["value"]["id"] = 11;
	node["mapProperty"][0]["value"][qrw::MetaClass::TYPE_NAME_YAML_KEY] = ValueStub::typeName.getStringId();
	node["mapProperty"][1]["key"]["id"] = 2;
	node["mapProperty"][1]["value"]["id"] = 22;
	node["mapProperty"][1]["value"][qrw::MetaClass::TYPE_NAME_YAML_KEY] = ValueStub::typeName.getStringId();

	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<KeyMetaClassMock>(KeyStub::typeName);
	metaManager.registerMetaClass<ValueStubMetaClass>(ValueStub::typeName);

	ReflectableStub reflectableStub;

	qrw::StdMapProperty<ReflectableStub,KeyStub,ValueStub> stdMapProperty(&ReflectableStub::mapProperty, "mapProperty", metaManager);

	// Act
	stdMapProperty.deserialize(&reflectableStub, node);

	// Assert Result
	ASSERT_EQ(reflectableStub.mapProperty.size(), 2);
	EXPECT_EQ(reflectableStub.mapProperty.at(KeyStub(1))->id, 11);
	EXPECT_EQ(reflectableStub.mapProperty.at(KeyStub(2))->id, 22);
}

TEST(StdMapProperty_Deserialize, If_yaml_node_is_empty_Then_property_is_empty)
{
	// Arrange
	YAML::Node node;
	node["mapProperty"] = std::vector<int>();

	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<KeyMetaClassMock>(KeyStub::typeName);
	metaManager.registerMetaClass<ValueStubMetaClass>(ValueStub::typeName);

	ReflectableStub reflectableStub;

	qrw::StdMapProperty<ReflectableStub,KeyStub,ValueStub> stdMapProperty(&ReflectableStub::mapProperty, "mapProperty", metaManager);

	// Act
	stdMapProperty.deserialize(&reflectableStub, node);

	// Assert
	EXPECT_THAT(reflectableStub.mapProperty, IsEmpty());
}