#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "core/prioritylist.hpp"

class PriorityList_When_iterating : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(PriorityList_When_iterating);
	CPPUNIT_TEST(If_list_is_initially_empty_Then_nothing_is_iterated);
    CPPUNIT_TEST(If_list_is_empty_after_removing_items_Then_noting_is_iterated);
    CPPUNIT_TEST(If_list_contains_items_Then_range_based_loop_iterates_them_in_correct_order);
	CPPUNIT_TEST_SUITE_END();

public:
    void If_list_is_initially_empty_Then_nothing_is_iterated()
    {
        qrw::PriorityList<std::string> priorityList;
        for(auto& item : priorityList)
        {
            CPPUNIT_FAIL("Due to empty list, this should not be reached");
        }
    }

    void If_list_is_empty_after_removing_items_Then_noting_is_iterated()
    {
        qrw::PriorityList<std::string> priorityList;
        priorityList.insert(100, "foo");
        priorityList.erase(100, "foo");

        for(auto& item : priorityList)
        {
            CPPUNIT_FAIL("Due to empty list, this should not be reached");
        }
    }

    void If_list_contains_items_Then_range_based_loop_iterates_them_in_correct_order()
    {
        qrw::PriorityList<std::string> priorityList;
        priorityList.insert( 90, "90:a");
        priorityList.insert(100, "100:a");
        priorityList.insert(100, "100:b");
        priorityList.insert(110, "110:a");

        std::string result = "";
        std::string expectedResult = "90:a,100:a,100:b,110:a,";

        for(auto& item : priorityList)
        {
            result += item + ",";
        }

        CPPUNIT_ASSERT_EQUAL(expectedResult, result);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(PriorityList_When_iterating);