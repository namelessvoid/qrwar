#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "engine/unit.hpp"
#include "engine/board.hpp"
#include "engine/square.hpp"
#include "engine/player.hpp"
#include "engine/coordinates.hpp"

class UnitTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UnitTest);
	CPPUNIT_TEST(attackTest);
	CPPUNIT_TEST(setGetSquareTest);
	CPPUNIT_TEST(canMoveToTestPlayerNotActive);
	CPPUNIT_TEST(canMoveToTestDestinationNotEmpty);
	CPPUNIT_TEST(canMoveToTestNotEnoughMovement);
	CPPUNIT_TEST(canMoveToTest);
	CPPUNIT_TEST(moveToTest);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			unit1 = new qrw::Unit(qrw::EUT_SWORDMAN, 5, 2, 1, 0, 0, 0, nullptr);
			unit2 = new qrw::Unit(qrw::EUT_SWORDMAN, 5, 3, 1, 0, 0, 0, nullptr);
		}

		void tearDown()
		{
			delete unit1;
			delete unit2;
		}

		void attackTest()
		{
			int mods[] = {0, 0};
			unit1->attack(unit2, mods, mods);
			CPPUNIT_ASSERT(unit1->getHP() == 3);
			CPPUNIT_ASSERT(unit2->getHP() == 4);
			unit2->attack(unit1, mods, mods);
			CPPUNIT_ASSERT(unit1->getHP() == 1);
			CPPUNIT_ASSERT(unit2->getHP() == 3);
			unit2->attack(unit1, mods, mods);
			CPPUNIT_ASSERT(unit1->getHP() == 0);
			CPPUNIT_ASSERT(unit2->getHP() == 3);
		}

		void setGetSquareTest()
		{
			qrw::Square square(1, 2);

			unit1->setSquare(&square);

			CPPUNIT_ASSERT(&square == unit1->getSquare());
		}

		void canMoveToTestPlayerNotActive()
		{
			qrw::Board board(3, 3);
			qrw::Player player;
			player.setActive(false);

			qrw::Unit unit(qrw::EUT_SPEARMAN, 5, 2, 1, 1, 3, &player, &board);

			CPPUNIT_ASSERT(unit.canMoveTo(qrw::Coordinates(1, 1)) == false);
		}

		void canMoveToTestDestinationNotEmpty()
		{
			qrw::Board board(3, 3);
			qrw::Player player;
			player.setActive(true);

			qrw::Unit blocker(qrw::EUT_SPEARMAN, 5, 2, 1, 1, 3, nullptr, &board);
			board.getSquare(2, 0)->setUnit(&blocker);

			qrw::Unit mover(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player, &board);
			board.getSquare(0, 0)->setUnit(&mover);

			CPPUNIT_ASSERT(mover.canMoveTo(qrw::Coordinates(2, 0)) == false);
		}

		void canMoveToTestNotEnoughMovement()
		{
			qrw::Board board(3, 3);
			qrw::Player player;
			player.setActive(true);

			qrw::Unit unit(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player, &board);
			unit.setSquare(board.getSquare(0, 0));
			board.getSquare(0, 0)->setUnit(&unit);

			unit.setCurrentMovement(1);

			CPPUNIT_ASSERT(unit.canMoveTo(qrw::Coordinates(2, 0)) == false);
		}

		void canMoveToTest()
		{
			qrw::Board board(3, 3);
			qrw::Player player;
			player.setActive(true);

			qrw::Unit unit(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player, &board);
			unit.setSquare(board.getSquare(0, 0));
			board.getSquare(0, 0)->setUnit(&unit);

			unit.setCurrentMovement(3);
			unit.canMoveTo(qrw::Coordinates(2, 0));

			CPPUNIT_ASSERT(unit.canMoveTo(qrw::Coordinates(2, 0)) == true);
		}

		void moveToTest()
		{
			qrw::Board board(3, 3);
			qrw::Player player;
			player.setActive(true);

			qrw::Unit unit(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player, &board);
			unit.setSquare(board.getSquare(0, 0));
			board.getSquare(0, 0)->setUnit(&unit);

			unit.setCurrentMovement(3);

			unit.moveTo(qrw::Coordinates(2, 0));

			CPPUNIT_ASSERT(board.getSquare(0, 0)->getUnit() == nullptr);
			CPPUNIT_ASSERT(board.getSquare(2, 0)->getUnit() == &unit);
			CPPUNIT_ASSERT(unit.getSquare() == board.getSquare(2, 0));
		}

	private:
		qrw::Unit* unit1;
		qrw::Unit* unit2;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest);
