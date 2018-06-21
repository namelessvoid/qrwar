#include <gtest/gtest.h>
#include <meta/metamanager.hpp>

#include "game/meta/boardmetaclass.hpp"

#include "meta/metamanager.hpp"

#include "engine/board.hpp"
#include "engine/terrain.hpp"

TEST(BoardMetaClass_Deserialize, InitializesAllProperties)
{
	qrw::Board board;

	const qrw::MetaClass* boardMetaClass = qrw::MetaManager::getMetaClassFor<qrw::Board>();

	YAML::Node node;
	node["_width"] = 12;
	node["_height"] = 13;
	node["terrains"] = std::vector<int>();

	boardMetaClass->deserialize(&board, node);

	EXPECT_EQ(board.getWidth(), 12);
	EXPECT_EQ(board.getHeight(), 13);
}