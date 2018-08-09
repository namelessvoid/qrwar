#include <gtest/gtest.h>
#include <meta/properties/tproperty.hpp>

#include "testdoubles.hpp"

TEST(TProperty_Deserialize, If_property_is_enum_Then_it_is_deserialized)
{
	// Arrange
	qrw::MetaManager metaManager;
	std::string propertyName = "enumProperty";
	qrw::TProperty enumProperty(&ReflectableStub::enumProperty, propertyName, metaManager);

	ReflectableStub reflectableStub;

	YAML::Node node;
	node[propertyName] = 1;

	// Act
	enumProperty.deserialize(&reflectableStub, node);

	// Assert
	EXPECT_EQ(reflectableStub.enumProperty, ReflectableStub::EnumType::ONE);
}