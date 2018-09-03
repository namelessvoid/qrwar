#include <gtest/gtest.h>

#include "meta/properties/tclassproperty.hpp"

#include "testdoubles.hpp"

using ::testing::_;
using ::testing::WhenDynamicCastTo;
using ::testing::Property;
using ::testing::Return;

TEST(TClassProperty_Deserialize, Then_property_is_deserialized)
{
	// Arrange
	std::string propertyName = "classProperty";

	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<ValueStubMetaClass>(ValueStub::typeName);

	qrw::TClassProperty<ReflectableStub,ValueStub> classProperty(&ReflectableStub::classProperty, propertyName, metaManager);

	ReflectableStub reflectableStub;
	YAML::Node node;
	node[propertyName]["id"] = 12;

	// Act
	classProperty.deserialize(&reflectableStub, node);

	// Assert
	EXPECT_EQ(reflectableStub.classProperty.id, 12);
}
