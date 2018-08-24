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
	node["mapProperty"][0]["key"] = "firstKey";
	node["mapProperty"][0]["value"] = "firstValue";
	node["mapProperty"][1]["key"] = "secondKey";
	node["mapProperty"][1]["value"] = "secondValue";

	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<KeyMetaClassMock>(KeyStub::typeName);
	metaManager.registerMetaClass<ValueStubMetaClass>(ValueStub::typeName);

	ReflectableStub reflectableStub;

	qrw::StdMapProperty<ReflectableStub,KeyStub,ValueStub> stdMapProperty(&ReflectableStub::mapProperty, "mapProperty", metaManager);

	// Assert Mocks
	auto keyMetaClassMock = static_cast<const KeyMetaClassMock*>(metaManager.getMetaClassFor<KeyStub>());
	auto valueMetaClassMock = static_cast<const ValueStubMetaClass*>(metaManager.getMetaClassFor<ValueStub>());

	EXPECT_CALL(*keyMetaClassMock, deserialize(Property(&YAML::Node::as<std::string>, "firstKey")))
		.WillOnce(Return(new KeyStub(1)));
	EXPECT_CALL(*keyMetaClassMock, deserialize(Property(&YAML::Node::as<std::string>, "secondKey")))
		.WillOnce(Return(new KeyStub(2)));
	EXPECT_CALL(*valueMetaClassMock, deserialize(Property(&YAML::Node::as<std::string>, "firstValue")))
		.WillOnce(Return(new ValueStub(1)));
	EXPECT_CALL(*valueMetaClassMock, deserialize(Property(&YAML::Node::as<std::string>, "secondValue")))
		.WillOnce(Return(new ValueStub(2)));

	// Act
	stdMapProperty.deserialize(&reflectableStub, node);

	// Assert Result
	ASSERT_EQ(reflectableStub.mapProperty.size(), 2);
	EXPECT_EQ(reflectableStub.mapProperty.at(KeyStub(1))->id, 1);
	EXPECT_EQ(reflectableStub.mapProperty.at(KeyStub(2))->id, 2);
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