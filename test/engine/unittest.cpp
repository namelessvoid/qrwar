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
	CPPUNIT_TEST(canAttackTestNoMovement);
	CPPUNIT_TEST(canAttackTestUnitOfSamePlayer);
	CPPUNIT_TEST(canAttackTestOutOfAttackRange);
	CPPUNIT_TEST(attackTest);
	CPPUNIT_TEST(attackTestDefenderDied);
	CPPUNIT_TEST(attackTestAttackerDied);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp()
		{
			board = new qrw::Board(3, 3);
			player1 = new qrw::Player();
			player2 = new qrw::Player();
			unit1 = new qrw::Unit(qrw::EUT_SWORDMAN, 5, 2, 1, 1, 4, player1, board);
			unit2 = new qrw::Unit(qrw::EUT_SWORDMAN, 5, 3, 1, 1, 4, player2, board);

			// Default position of units
			unit1->setSquare(board->getSquare(0, 0));
			unit1->getSquare()->setUnit(unit1);

			unit2->setSquare(board->getSquare(0, 1));
			unit2->getSquare()->setUnit(unit2);
		}

		void tearDown()
		{
			delete unit1;
			delete unit2;
			delete player1;
			delete player2;
			delete board;
		}

		void setHPTest()
		{
			unit1->setHP(2);
			CPPUNIT_ASSERT_EQUAL(2, unit1->getHP());

			unit1->setHP(-4);
			CPPUNIT_ASSERT_EQUAL(0, unit1->getHP());
		}

		void setGetSquareTest()
		{
			qrw::Square square(1, 2);

			unit1->setSquare(&square);

			CPPUNIT_ASSERT(&square == unit1->getSquare());
		}

		void removeFromBoardTest()
		{
			qrw::Square* square = board->getSquare(0, 0);
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

		void canMoveToTestPlayerNotActive()
		{
			player1->setActive(false);
			CPPUNIT_ASSERT(unit1->canMoveTo(qrw::Coordinates(1, 1)) == nullptr);
		}

		void canMoveToTestDestinationNotEmpty()
		{
			player1->setActive(true);
			board->getSquare(0, 0)->setUnit(unit1);
			board->getSquare(2, 0)->setUnit(unit2);

			CPPUNIT_ASSERT(unit1->canMoveTo(qrw::Coordinates(2, 0)) == nullptr);
		}

		void canMoveToTestNotEnoughMovement()
		{
			player1->setActive(true);

			unit1->setSquare(board->getSquare(0, 0));
			unit1->getSquare()->setUnit(unit1);

			unit1->setCurrentMovement(1);

			CPPUNIT_ASSERT(unit1->canMoveTo(qrw::Coordinates(2, 0)) == nullptr);
		}

		void canMoveToTest()
		{
			player1->setActive(true);

			unit1->setSquare(board->getSquare(0, 0));
			unit1->getSquare()->setUnit(unit1);
			unit1->setCurrentMovement(3);

			unit1->canMoveTo(qrw::Coordinates(2, 0));
			CPPUNIT_ASSERT(unit1->canMoveTo(qrw::Coordinates(2, 0)) != nullptr);
		}

		void moveToTest()
		{
			player1->setActive(true);

			unit1->setSquare(board->getSquare(0, 0));
			unit1->getSquare()->setUnit(unit1);
			unit1->setCurrentMovement(3);

			unit1->moveTo(qrw::Coordinates(2, 0));

			// Check if squares are updated
			CPPUNIT_ASSERT(board->getSquare(0, 0)->getUnit() == nullptr);
			CPPUNIT_ASSERT(board->getSquare(2, 0)->getUnit() == unit1);
			// Check if unit has updated square
			CPPUNIT_ASSERT(unit1->getSquare() == board->getSquare(2, 0));
			// Check if movement was substracted correctly
			CPPUNIT_ASSERT(unit1->getCurrentMovement() == 1);
		}

		void canAttackTest()
		{
			player1->setActive(true);

			unit1->setSquare(board->getSquare(0, 0));
			unit1->getSquare()->setUnit(unit1);

			unit2->setSquare(board->getSquare(0, 1));
			unit2->getSquare()->setUnit(unit2);

			CPPUNIT_ASSERT(unit1->canAttack(unit2));
		}

		void canAttackTestPlayerNotActive()
		{
			player1->setActive(false);

			CPPUNIT_ASSERT_EQUAL(false, unit1->canAttack(unit2));
		}

		void canAttackTestNoMovement()
		{
			player1->setActive(true);
			unit1->setCurrentMovement(0);

			CPPUNIT_ASSERT_EQUAL(false, unit1->canAttack(unit2));
		}

		void canAttackTestUnitOfSamePlayer()
		{
			player1->setActive(true);
			unit2->setPlayer(player1);

			CPPUNIT_ASSERT_EQUAL(false, unit1->canAttack(unit2));
		}

		void canAttackTestOutOfAttackRange()
		{
			player1->setActive(true);

			unit2->removeFromBoard();
			unit2->setSquare(board->getSquare(2, 2));
			unit2->getSquare()->setUnit(unit2);

			CPPUNIT_ASSERT_EQUAL(false, unit1->canAttack(unit2));
		}

		void attackTest()
		{
			player1->setActive(true);

			// Set up terrain
			qrw::Terrain terrain1(qrw::ET_HILL, -1, +1);
			board->getSquare(0, 0)->setTerrain(&terrain1);

			qrw::Terrain terrain2(qrw::ET_HILL, +2, -1);
			board->getSquare(0, 1)->setTerrain(&terrain2);

			qrw::Unit::AttackResult result = unit1->attack(unit2);

			CPPUNIT_ASSERT_EQUAL(true, result.attackPerformed);
			CPPUNIT_ASSERT_EQUAL(3, result.attackerHPDelta);
			CPPUNIT_ASSERT_EQUAL(1, result.defenderHPDelta);

			CPPUNIT_ASSERT_EQUAL(2, unit1->getHP());
			CPPUNIT_ASSERT_EQUAL(4, unit2->getHP());

			// Check if attackPerformed is false if attacking was not able.
			result = unit2->attack(unit1);

			CPPUNIT_ASSERT_EQUAL(false, result.attackPerformed);
		}

		void attackTestDefenderDied()
		{
			player1->setActive(true);
			unit2->setHP(1);

			qrw::Square* unit2Square = unit2->getSquare();

			unit1->attack(unit2);

			CPPUNIT_ASSERT_EQUAL(0, unit2->getHP());
			// Check if unit2 was removed from board
			CPPUNIT_ASSERT(unit2->getSquare() == nullptr);
			CPPUNIT_ASSERT(unit2Square->getUnit() == nullptr);
		}

		void attackTestAttackerDied()
		{
			player1->setActive(true);
			unit1->setHP(1);

			qrw::Square* unit1Square = unit1->getSquare();

			unit1->attack(unit2);

			CPPUNIT_ASSERT_EQUAL(0, unit1->getHP());
			CPPUNIT_ASSERT_EQUAL(4, unit2->getHP());
			// Check if unit1 was removed from board
			CPPUNIT_ASSERT(unit1->getSquare() == nullptr);
			CPPUNIT_ASSERT(unit1Square->getUnit() == nullptr);
		}

	private:
		qrw::Board* board;
		qrw::Player* player1;
		qrw::Player* player2;
		qrw::Unit* unit1;
		qrw::Unit* unit2;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest);
