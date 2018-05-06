#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "core/prioritylist.hpp"

class PriorityList_Clear : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(PriorityList_Clear);
	CPPUNIT_TEST(Then_list_is_empty);
	CPPUNIT_TEST_SUITE_END();

public:
    void Then_list_is_empty()
    {
        qrw::PriorityList<std::string> priorityList;
        priorityList.insert(100, "element1");
        priorityList.insert(200, "element1");
        priorityList.insert(200, "element2");

        priorityList.clear();

        CPPUNIT_ASSERT(priorityList.begin() == priorityList.end());
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(PriorityList_Clear);