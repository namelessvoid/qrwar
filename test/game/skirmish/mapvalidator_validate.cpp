#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "core/logger.hpp"

#include "game/skirmish/mapvalidator.hpp"

class MapValidator_validate : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(MapValidator_validate);
    CPPUNIT_TEST(If_map_is_valid_Then_true_should_be_returned);
    CPPUNIT_TEST(If_map_content_does_have_only_one_document_Then_validation_fails);
    CPPUNIT_TEST(If_object_does_not_contain_type_key_Then_validation_fails);
    CPPUNIT_TEST(If_object_has_unsupported_type_Then_validation_fails);
    CPPUNIT_TEST(If_objects_do_not_contain_board_Then_validation_fails);
    CPPUNIT_TEST(If_objects_contain_less_than_two_deployment_zones_Then_validation_fails);
	CPPUNIT_TEST_SUITE_END();

public:
    void If_map_is_valid_Then_true_should_be_returned()
    {
        // Arrange
        qrw::MapValidator mapValidator;

        std::vector<YAML::Node> document = createValidMapContent();

        // Act
        bool validationResult = mapValidator.validate(document);

        // Assert
        CPPUNIT_ASSERT(validationResult == true);
    }

    void If_map_content_does_have_only_one_document_Then_validation_fails()
    {
        // Arrange
        std::stringstream logStream;
        qrw::Logger* log = new qrw::Logger(logStream, logStream, logStream);

        qrw::MapValidator mapValidator(log);

        auto document = createValidMapContent();
        document.pop_back();

        const std::string expectedWarning = "(warn) MapValidator: Map must contain exactly 2 yaml documents (description and content)\n";

        // Act
        bool validationResult = mapValidator.validate(document);

        // Assert
        CPPUNIT_ASSERT(validationResult == false);
        CPPUNIT_ASSERT_EQUAL(expectedWarning, logStream.str());
    }

    void If_object_does_not_contain_type_key_Then_validation_fails()
    {
        // Arrange
        std::stringstream logStream;
        qrw::Logger* log = new qrw::Logger(logStream, logStream, logStream);

        qrw::MapValidator mapValidator(log);

        auto documents = createValidMapContent();
        documents[1][0].remove("type");

        const std::string expectedWarning = "(warn) MapValidator: Object does not contain mandatory \"type\" key\n";

        // Act
        bool validationResult = mapValidator.validate(documents);

        // Assert
        CPPUNIT_ASSERT(validationResult == false);
        CPPUNIT_ASSERT_EQUAL(expectedWarning, logStream.str());
    }

    void If_object_has_unsupported_type_Then_validation_fails()
    {
        // Arrange
        std::stringstream logStream;
        qrw::Logger* log = new qrw::Logger(logStream, logStream, logStream);

        qrw::MapValidator mapValidator(log);

        auto documents = createValidMapContent();
        documents[1][0]["type"] = "qrw::Cursor";

        const std::string expectedWarning = "(warn) MapValidator: Object has invalid \"type\": \"qrw::Cursor\"\n";

        // Act
        bool validationResult = mapValidator.validate(documents);

        // Assert
        CPPUNIT_ASSERT(validationResult == false);
        CPPUNIT_ASSERT_EQUAL(expectedWarning, logStream.str());       
    }

    void If_objects_do_not_contain_board_Then_validation_fails()
    {
        // Arrange
        std::stringstream logStream;
        qrw::Logger* log = new qrw::Logger(logStream, logStream, logStream);

        qrw::MapValidator mapValidator(log);

        auto documents = createValidMapContent();
        auto objects = documents[1].as<std::vector<YAML::Node>>();
        objects.erase(objects.begin());
        documents[1] = objects;

        std::cout << documents[1] << std::endl << std::flush;

        std::string expectedWarning = "(warn) MapValidator: Map must contain exactly one \"qrw::Board\"\n";

        // Act
        bool validationResult = mapValidator.validate(documents);

        // Assert
        CPPUNIT_ASSERT(validationResult == false);
        CPPUNIT_ASSERT_EQUAL(expectedWarning, logStream.str());
    }

    void If_objects_contain_less_than_two_deployment_zones_Then_validation_fails()
    {
        // Arrange
        std::stringstream logStream;
        qrw::Logger* log = new qrw::Logger(logStream, logStream, logStream);

        qrw::MapValidator mapValidator(log);

        auto documents = createValidMapContent();
        auto objects = documents[1].as<std::vector<YAML::Node>>();
        objects.erase(++objects.begin());
        documents[1] = objects;

        std::cout << documents[1] << std::endl << std::flush;

        std::string expectedWarning = "(warn) MapValidator: Map must contain at least two \"qrw::DeploymentZone\"s\n";

        // Act
        bool validationResult = mapValidator.validate(documents);

        // Assert
        CPPUNIT_ASSERT(validationResult == false);
        CPPUNIT_ASSERT_EQUAL(expectedWarning, logStream.str());
    }

private:
    std::vector<YAML::Node> createValidMapContent()
    {
        return YAML::LoadAll(
            "---\n"
            "name: MapValidator Test Map\n"
            "short-description: This is a map to test the MapValidator\n"
            "player-count: 2\n"
            "---\n"
            "- type: qrw::Board\n"
            "  size:\n"
            "    width: 16\n"
            "    height: 10\n"
            "- type: qrw::DeploymentZone\n"
            "- type: qrw::DeploymentZone\n"
        );
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MapValidator_validate);