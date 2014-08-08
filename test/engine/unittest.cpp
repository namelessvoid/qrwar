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
	CPPUNIT_TEST(setHPTest);
	CPPUNIT_TEST(setGetSquareTest);
	CPPUNIT_TEST(removeFromBoardTest);
	CPPUNIT_TEST(getModifiedAttackAndDefenseTest);
	CPPUNIT_TEST(getModifiedAttackAndDefenseTestWithoutTerrain);
	// movement
	CPPUNIT_TEST(canMoveToTestPlayerNotActive);
	CPPUNIT_TEST(canMoveToTestDestinationNotEmpty);
	CPPUNIT_TEST(canMoveToTestNotEnoughMovement);
	CPPUNIT_TEST(canMoveToTest);
	CPPUNIT_TEST(moveToTest);
	// attack
	CPPUNIT_TEST(canAttackTest);
	CPPUNIT_TEST(canAttackTestPlayerNotActive);
	CPPUNIT_TEST(canAttackTestUnitOfSamePlayer);
	CPPUNIT_TEST(canAttackTestOutOfAttackRange);
	CPPUNIT_TEST(attackTest);
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

		void setHPTest()
		{
			unit1->setHP(2);
			CPPUNIT_ASSERT_EQUAL(2, unit1->getHP());

			unit1->setHP(-4);
			CPPUNIT_ASSERT_EQUAL(0, unit1->getHP());
		}

		void removeFromBoardTest()
		{
			qrw::Board board(3, 3);
			qrw::Square* square = board.getSquare(0, 0);
			unit1->setSquare(square);
			square->setUnit(unit1);

			unit1->removeFromBoard();

			CPPUNIT_ASSERT(square->getUnit() == nullptr);
			CPPUNIT_ASSERT(unit1->getSquare() == nullptr);
		}

		void getModifiedAttackAndDefenseTest()
		{
			// Test values > 0
			qrw::Square square(0, 0);
			qrw::Terrain terrain(qrw::ET_HILL, 1, -1);
			square.setTerrain(&terrain);

			unit1->setSquare(&square);

			CPPUNIT_ASSERT_EQUAL(3, unit1->getModifiedAttack());
			CPPUNIT_ASSERT_EQUAL(0, unit1->getModifiedDefense());

			// Test values < 0
			qrw::Terrain terrain2(qrw::ET_WALL, -3, -12);
			square.setTerrain(&terrain2);

			CPPUNIT_ASSERT_EQUAL(0, unit1->getModifiedAttack());
			CPPUNIT_ASSERT_EQUAL(0, unit1->getModifiedDefense());
		}

		void getModifiedAttackAndDefenseTestWithoutTerrain()
		{
			qrw::Square square(0, 0);
			unit1->setSquare(&square);

			CPPUNIT_ASSERT_EQUAL(2, unit1->getModifiedAttack());
			CPPUNIT_ASSERT_EQUAL(1, unit1->getModifiedDefense());
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

			CPPUNIT_ASSERT(unit.canMoveTo(qrw::Coordinates(1, 1)) == nullptr);
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

			CPPUNIT_ASSERT(mover.canMoveTo(qrw::Coordinates(2, 0)) == nullptr);
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

			CPPUNIT_ASSERT(unit.canMoveTo(qrw::Coordinates(2, 0)) == nullptr);
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

			CPPUNIT_ASSERT(unit.canMoveTo(qrw::Coordinates(2, 0)) != nullptr);
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

			// Check if squares are updated
			CPPUNIT_ASSERT(board.getSquare(0, 0)->getUnit() == nullptr);
			CPPUNIT_ASSERT(board.getSquare(2, 0)->getUnit() == &unit);
			// Check if unit has updated square
			CPPUNIT_ASSERT(unit.getSquare() == board.getSquare(2, 0));
			// Check if movement was substracted correctly
			CPPUNIT_ASSERT(unit.getCurrentMovement() == 1);
		}

		void canAttackTest()
		{
			qrw::Board board(3, 3);

			qrw::Player player1;
			player1.setActive(true);

			qrw::Player player2;
			player2.setActive(false);

			qrw::Unit attacker(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player1, &board);
			qrw::Unit defender(qrw::EUT_SPEARMAN, 5, 2, 2, 1, 3, &player2, &board);

			board.getSquare(0, 0)->setUnit(&attacker);
			attacker.setSquare(board.getSquare(0, 0));

			board.getSquare(0, 1)->setUnit(&defender);
			defender.setSquare(board.getSquare(0, 1));

			CPPUNIT_ASSERT(attacker.canAttack(&defender));
		}

		void canAttackTestPlayerNotActive()
		{
			qrw::Board board(3, 3);
			qrw::Player player;
			player.setActive(false);

			qrw::Unit attacker(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player, &board);
			qrw::Unit defender(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player, &board);

			CPPUNIT_ASSERT_EQUAL(false, attacker.canAttack(&defender));
		}

		void canAttackTestUnitOfSamePlayer()
		{
			qrw::Board board(3, 3);
			qrw::Player player;
			player.setActive(true);

			qrw::Unit attacker(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player, &board);
			qrw::Unit defender(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player, &board);

			board.getSquare(0, 0)->setUnit(&attacker);
			attacker.setSquare(board.getSquare(0, 0));

			board.getSquare(0, 1)->setUnit(&defender);
			defender.setSquare(board.getSquare(0, 1));

			CPPUNIT_ASSERT_EQUAL(false, attacker.canAttack(&defender));
		}

		void canAttackTestOutOfAttackRange()
		{
			qrw::Board board(3, 3);
			qrw::Player player1;
			qrw::Player player2;
			player1.setActive(true);

			qrw::Unit attacker(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player1, &board);
			qrw::Unit defender(qrw::EUT_ARCHER, 5, 2, 1, 1, 3, &player2, &board);

			board.getSquare(0, 0)->setUnit(&attacker);
			attacker.setSquare(board.getSquare(0, 0));

			board.getSquare(0, 2)->setUnit(&defender);
			defender.setSquare(board.getSquare(0, 2));

			CPPUNIT_ASSERT_EQUAL(false, attacker.canAttack(&defender));
		}

		void attackTest()
		{
			qrw::Board board(2, 2);

			qrw::Terrain terrain1(qrw::ET_HILL, -1, +1);
			qrw::Player  player1;
			qrw::Unit attacker(qrw::EUT_SPEARMAN, 5, 2, 1, 1, 3, &player1, &board);

			player1.setActive(true);
			board.getSquare(0, 0)->setTerrain(&terrain1);
			board.getSquare(0, 0)->setUnit(&attacker);
			attacker.setSquare(board.getSquare(0, 0));

			qrw::Terrain terrain2(qrw::ET_HILL, +2, -1);
			qrw::Player player2;
			qrw::Unit defender(qrw::EUT_SPEARMAN, 5, 2, 1, 1, 3, &player2, &board);

			board.getSquare(0, 1)->setTerrain(&terrain2);
			board.getSquare(0, 1)->setUnit(&defender);
			defender.setSquare(board.getSquare(0, 1));

			qrw::Unit::AttackResult result = attacker.attack(&defender);

			CPPUNIT_ASSERT_EQUAL(true, result.attackPerformed);
			CPPUNIT_ASSERT_EQUAL(2, result.attackerHPDelta);
			CPPUNIT_ASSERT_EQUAL(1, result.defenderHPDelta);

			CPPUNIT_ASSERT_EQUAL(3, attacker.getHP());
			CPPUNIT_ASSERT_EQUAL(4, defender.getHP());

			// Check if attackPerformed is false if attacking was not able.
			result = defender.attack(&attacker);

			CPPUNIT_ASSERT_EQUAL(false, result.attackPerformed);
		}

	private:
		qrw::Unit* unit1;
		qrw::Unit* unit2;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest);
