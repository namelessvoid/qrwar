#include <gtest/gtest.h>

#include "meta/properties/tclassproperty.hpp"

#include "testdoubles.hpp"

using ::testing::_;
using ::testing::WhenDynamicCastTo;
using ::testing::Property;

TEST(TClassProperty_Deserialize, Then_property_is_deserialized)
{
	// Arrange
	std::string propertyName = "classProperty";
	std::string propertyValue = "ValueStubMetaClass::deserialize called";

	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<ValueStubMetaClass>(ValueStub::typeName);

	auto valueStubMetaClass = static_cast<const ValueStubMetaClass*>(metaManager.getMetaClassFor<ValueStub>());
	EXPECT_CALL(*valueStubMetaClass, deserialize(WhenDynamicCastTo<ValueStub*>(_), Property(&YAML::Node::as<std::string>, propertyValue)))
			.WillOnce(DeserializeValue(12));

	qrw::TClassProperty<ReflectableStub,ValueStub> classProperty(&ReflectableStub::classProperty, propertyName, metaManager);

	ReflectableStub reflectableStub;
	YAML::Node node;
	node[propertyName] = propertyValue;

	// Act
	classProperty.deserialize(&reflectableStub, node);

	// Assert
	EXPECT_EQ(reflectableStub.classProperty.id, 12);
}