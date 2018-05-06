#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "core/logger.hpp"

class Logger_Log : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(Logger_Log);
    CPPUNIT_TEST(If_log_information_Then_message_is_written_to_information_stream);
    CPPUNIT_TEST(If_log_warning_Then_message_is_written_to_warning_stream);
    CPPUNIT_TEST(If_log_error_Then_message_is_written_to_error_stream);
    CPPUNIT_TEST(If_prefix_is_defined_Then_it_is_included_in_logs);
	CPPUNIT_TEST_SUITE_END();

public:
    void If_log_information_Then_message_is_written_to_information_stream()
    {
        std::stringstream informationStream;
        std::stringstream warningStream;
        std::stringstream errorStream;

        std::string message = "this is some information";

        qrw::Logger log(informationStream, warningStream, errorStream);

        log.logInformation(message);

        std::string content = informationStream.str();
        CPPUNIT_ASSERT(content.find(message) != std::string::npos);
    }

    void If_log_warning_Then_message_is_written_to_warning_stream()
    {
        std::stringstream informationStream;
        std::stringstream warningStream;
        std::stringstream errorStream;

        std::string message = "this is some warning";

        qrw::Logger log(informationStream, warningStream, errorStream);

        log.logWarning(message);

        std::string content = warningStream.str();
        CPPUNIT_ASSERT(content.find(message) != std::string::npos);
    }

    void If_log_error_Then_message_is_written_to_error_stream()
    {
        std::stringstream informationStream;
        std::stringstream warningStream;
        std::stringstream errorStream;

        std::string message = "this is some error";

        qrw::Logger log(informationStream, warningStream, errorStream);

        log.logError(message);

        std::string content = errorStream.str();
        CPPUNIT_ASSERT(content.find(message) != std::string::npos);
    }

    void If_prefix_is_defined_Then_it_is_included_in_logs()
    {
        std::stringstream stream;

        qrw::Logger log(stream, stream, stream);
        log.setPrefix("ThisIsPrefix");

        log.logInformation("some information");

        std::string content = stream.str();
        CPPUNIT_ASSERT(content.find("ThisIsPrefix") != std::string::npos);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(Logger_Log);