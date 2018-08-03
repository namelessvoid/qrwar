#include <gtest/gtest.h>

#include "meta/properties/tclassproperty.hpp"

#include "testdoubles.hpp"

using ::testing::_;

TEST(TClassProperty_Serialize, Then_serializes_property_correctly)
{
	// Arrange
	std::string propertyName = "classProperty";
	std::string propertyValue = "ValueStubMetaClass::serialize called";
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<ValueStubMetaClass>(ValueStub::typeName);

	auto valueStubMetaClass = static_cast<const ValueStubMetaClass*>(metaManager.getMetaClassFor<ValueStub>());
	EXPECT_CALL(*valueStubMetaClass, serialize(_, _))
				.WillOnce(SerializeToYaml(propertyValue));

	qrw::TClassProperty classProperty(&ReflectableStub::classProperty, propertyName, metaManager);

	ReflectableStub reflectableStub;

	YAML::Emitter out;

	// Act
	out << YAML::BeginMap;
	classProperty.serialize(&reflectableStub, out);
	out << YAML::EndMap;

	// Assert
	YAML::Node result = YAML::Load(out.c_str());

	ASSERT_TRUE(result[propertyName]);
	EXPECT_EQ(result[propertyName].as<std::string>(), propertyValue);
}
