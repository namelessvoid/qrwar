#include <gtest/gtest.h>

#include "meta/properties/tproperty.hpp"
#include "testdoubles.hpp"

TEST(TProperty_Serialize, If_property_is_enum_Then_it_is_serialized)
{
	// Arrange
	qrw::MetaManager metaManager;

	std::string propertyName = "enumProperty";
	qrw::TProperty enumProperty(&ReflectableStub::enumProperty, propertyName, metaManager);

	ReflectableStub reflectableStub;
	reflectableStub.enumProperty = ReflectableStub::EnumType::ONE;

	YAML::Emitter out;

	// Act
	out << YAML::BeginMap;
	enumProperty.serialize(&reflectableStub, out);
	out << YAML::EndMap;

	// Assert
	YAML::Node result = YAML::Load(out.c_str());

	ASSERT_TRUE(result[propertyName]) << "Key '" << propertyName << "' does not exist";
	EXPECT_EQ(result[propertyName].as<int>(), 1);
}