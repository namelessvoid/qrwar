#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "core/prioritylist.hpp"

class PriorityList_Contains : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(PriorityList_Contains);
	CPPUNIT_TEST(If_list_contains_element_Then_true_should_be_returned);
    CPPUNIT_TEST(If_list_does_not_contain_element_Then_false_should_be_returned);
	CPPUNIT_TEST_SUITE_END();

public:
    void If_list_contains_element_Then_true_should_be_returned()
    {
        qrw::PriorityList<std::string> priorityList;
        priorityList.insert(100, "element1");
        priorityList.insert(200, "element1");
        priorityList.insert(200, "element2");

        CPPUNIT_ASSERT(priorityList.contains(100, "element1"));
        CPPUNIT_ASSERT(priorityList.contains(200, "element1"));
        CPPUNIT_ASSERT(priorityList.contains(200, "element2"));
    }

    void If_list_does_not_contain_element_Then_false_should_be_returned()
    {
        qrw::PriorityList<std::string> priorityList;
        priorityList.insert(100, "element1");

        CPPUNIT_ASSERT(!priorityList.contains(100, "element2"));
        CPPUNIT_ASSERT(!priorityList.contains(200, "element1"));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(PriorityList_Contains);