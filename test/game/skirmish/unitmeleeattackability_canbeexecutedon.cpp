#include <gtest/gtest.h>

#include "helpers.hpp"

#include "engine/board.hpp"
#include "game/skirmish/unit.hpp"
#include "game/skirmish/unitmeleeattackability.hpp"
#include "game/skirmish/wall.hpp"

using namespace qrw;

class UnitMock : public Unit
{
public:
	void setPlayer(std::shared_ptr<Player>& player) override { Unit::setPlayer(player); }
};

TEST(UnitMeleeAttackAbility_CanBeExecutedOn, If_there_is_no_opponent_Then_false_is_returned)
{
	// Arrange
	clearScene();

	Board* board = new Board(7, 7);
	g_scene.addGameObject(board);

	UnitMock unit;
	unit.setPosition({0, 0});
	UnitMeleeAttackAbility meleeAttackAbility(&unit);

	// Act
	bool canBeExecuted = meleeAttackAbility.canBeExecutedOn({0, 1});

	// Assert
	ASSERT_FALSE(canBeExecuted);
}

TEST(UnitMeleeAttackAbility_CanBeExecutedOn, If_there_is_a_friendly_unit_Then_false_is_returned)
{
	// Arrange
	clearScene();

	Board* board = new Board(7, 7);
	g_scene.addGameObject(board);

	UnitMock unit;
	unit.setPosition({0, 0});
	auto player1 = std::make_shared<Player>();
	unit.setPlayer(player1);
	UnitMeleeAttackAbility meleeAttackAbility(&unit);

	UnitMock friendlyUnit;
	friendlyUnit.setPlayer(player1);
	board->setUnit({0, 1}, &friendlyUnit);

	// Act
	bool canBeExecuted = meleeAttackAbility.canBeExecutedOn({0, 1});

	// Assert
	ASSERT_FALSE(canBeExecuted);
}

TEST(UnitMeleeAttackAbility_CanBeExecutedOn, If_there_is_an_opponent_Then_true_is_returned)
{
	// Arrange
	clearScene();

	Board* board = new Board(7, 7);
	g_scene.addGameObject(board);

	UnitMock unit;
	unit.setPosition({0, 0});
	auto player1 = std::make_shared<Player>();
	unit.setPlayer(player1);
	UnitMeleeAttackAbility meleeAttackAbility(&unit);

	UnitMock opponent;
	auto player2 = std::make_shared<Player>();
	opponent.setPlayer(player2);
	board->setUnit({0, 1}, &opponent);

	// Act
	bool canBeExecuted = meleeAttackAbility.canBeExecutedOn({0, 1});

	// Assert
	ASSERT_TRUE(canBeExecuted);
}

TEST(UnitMeleeAttackAbility_CanBeExecutedOn, If_opponent_is_out_of_range_Then_false_is_returned)
{
	// Arrange
	clearScene();

	Board* board = new Board(7, 7);
	g_scene.addGameObject(board);

	UnitMock unit;
	unit.setPosition({0, 0});
	auto player1 = std::make_shared<Player>();
	unit.setPlayer(player1);
	UnitMeleeAttackAbility meleeAttackAbility(&unit);

	UnitMock opponent;
	auto player2 = std::make_shared<Player>();
	opponent.setPlayer(player2);
	board->setUnit({0, 2}, &opponent);

	// Act
	bool canBeExecuted = meleeAttackAbility.canBeExecutedOn({0, 2});

	// Assert
	ASSERT_FALSE(canBeExecuted);
}

TEST(UnitMeleeAttackAbility_CanBeExecutedOn, If_unit_as_no_movement_left_Then_false_is_returned)
{
	// Arrange
	clearScene();

	Board* board = new Board(7, 7);
	g_scene.addGameObject(board);

	UnitMock unit;
	unit.setPosition({0, 0});
	auto player1 = std::make_shared<Player>();
	unit.setPlayer(player1);
	unit.setCurrentMovement(0);
	UnitMeleeAttackAbility meleeAttackAbility(&unit);

	UnitMock opponent;
	auto player2 = std::make_shared<Player>();
	opponent.setPlayer(player2);
	board->setUnit({0, 1}, &opponent);

	// Act
	bool canBeExecuted = meleeAttackAbility.canBeExecutedOn({0, 1});

	// Assert
	ASSERT_FALSE(canBeExecuted);
}

TEST(UnitMeleeAttackAbility_CanBeExecutedOn, If_attack_is_prevented_by_structure_Then_false_is_returned)
{
	// Arrange
	clearScene();

	Board* board = new Board(7, 7);
	g_scene.addGameObject(board);

	UnitMock unit;
	unit.setPosition({0, 0});
	auto player1 = std::make_shared<Player>();
	unit.setPlayer(player1);
	UnitMeleeAttackAbility meleeAttackAbility(&unit);

	UnitMock opponent;
	auto player2 = std::make_shared<Player>();
	opponent.setPlayer(player2);
	board->setUnit({0, 1}, &opponent);

	Wall wall;
	board->setStructure({0, 1}, &wall);

	// Act
	bool canBeExecuted = meleeAttackAbility.canBeExecutedOn({0, 1});

	// Assert
	ASSERT_FALSE(canBeExecuted);
}