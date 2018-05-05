#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "core/prioritylist.hpp"

class PriorityListIterator_Operator_equals : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(PriorityListIterator_Operator_equals);
    CPPUNIT_TEST(If_iterators_belong_to_different_lists_They_should_not_be_equal);
	CPPUNIT_TEST(If_is_begin_Then_it_should_equal_begin);
    CPPUNIT_TEST(If_is_intermediate_Then_it_should_equal_intermediate);
    CPPUNIT_TEST(If_is_end_Then_it_should_equal_end);
    CPPUNIT_TEST(If_iterator_advanced_to_end_It_should_equal_end);
	CPPUNIT_TEST_SUITE_END();

public:
    void If_iterators_belong_to_different_lists_They_should_not_be_equal()
    {
        qrw::PriorityList<std::string> list1;
        qrw::PriorityList<std::string> list2;

        CPPUNIT_ASSERT(!(list1.begin() == list2.begin()));
    }

    void If_is_begin_Then_it_should_equal_begin()
    {
        qrw::PriorityList<std::string> priorityList;
        priorityList.insert(100, "element");

        auto begin = priorityList.begin();

        CPPUNIT_ASSERT(begin == priorityList.begin());
    }

    void If_is_intermediate_Then_it_should_equal_intermediate()
    {
        qrw::PriorityList<std::string> priorityList;
        priorityList.insert(100, "element");
        priorityList.insert(100, "element2");

        auto iter1 = ++priorityList.begin();
        auto iter2 = ++priorityList.begin();

        CPPUNIT_ASSERT(iter1 == iter2);
    }

    void If_is_end_Then_it_should_equal_end()
    {
        qrw::PriorityList<std::string> priorityList;
        priorityList.insert(100, "element");

        auto end = priorityList.end();

        CPPUNIT_ASSERT(end == priorityList.end());
    }

    void If_iterator_advanced_to_end_It_should_equal_end()
    {
        qrw::PriorityList<std::string> priorityList;
        priorityList.insert( 90, "90:a");
        priorityList.insert(100, "100:a");

        auto iter = priorityList.begin();
        ++iter;
        ++iter;

        CPPUNIT_ASSERT(iter == priorityList.end());
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(PriorityListIterator_Operator_equals);