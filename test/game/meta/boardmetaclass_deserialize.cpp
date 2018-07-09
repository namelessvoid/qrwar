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
	node["_terrains"][0]["key"]["_x"] = 10;
	node["_terrains"][0]["key"]["_y"] = 11;
	node["_terrains"][0]["value"]["type"] = 1;
	node["_terrains"][0]["value"]["position"]["x"] = 10;
	node["_terrains"][0]["value"]["position"]["y"] = 11;

	boardMetaClass->deserialize(&board, node);

	EXPECT_EQ(board.getWidth(), 12);
	EXPECT_EQ(board.getHeight(), 13);
	EXPECT_EQ(board.getTerrains().size(), 1);
}