#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/board.hpp"

class BoardTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(BoardTest);
	CPPUNIT_TEST(getSquareTest);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			board = new qrw::Board(3, 5);
		}

		void tearDown()
		{
			delete board;
		}

		void getSquareTest()
		{
			CPPUNIT_ASSERT(board->getSquare(1, 1) != 0);
			CPPUNIT_ASSERT(board->getSquare(0, 0) != 0);
			CPPUNIT_ASSERT(board->getSquare(2, 4) != 0);

			CPPUNIT_ASSERT(board->getSquare(-1, 0) == 0);
			CPPUNIT_ASSERT(board->getSquare(0, -1) == 0);
			CPPUNIT_ASSERT(board->getSquare(3, 0) == 0);
			CPPUNIT_ASSERT(board->getSquare(0, 5) == 0);
		}

	private:
		qrw::Board* board;
};

CPPUNIT_TEST_SUITE_REGISTRATION(BoardTest);
