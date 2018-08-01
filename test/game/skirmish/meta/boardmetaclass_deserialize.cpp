#include <gtest/gtest.h>

#include "meta/metamanager.hpp"

#include "game/skirmish/meta/boardmetaclass.hpp"
#include "game/skirmish/meta/coordinatemetaclass.hpp"
#include "game/skirmish/meta/terrainmetaclass.hpp"

#include "meta/metamanager.hpp"

#include "engine/board.hpp"
#include "engine/terrain.hpp"

TEST(BoardMetaClass_Deserialize, Then_all_properties_are_initialized)
{
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<qrw::BoardMetaClass>(qrw::Board::typeName);
	metaManager.registerMetaClass<qrw::CoordinateMetaClass>(qrw::Coordinates::typeName);
	metaManager.registerMetaClass<qrw::TerrainMetaClass>(qrw::Terrain::typeName);

	qrw::Board board;

	const qrw::MetaClass* boardMetaClass = metaManager.getMetaClassFor<qrw::Board>();

	YAML::Node node;
	node["_width"] = 12;
	node["_height"] = 13;
	node["_terrains"][0]["key"]["_x"] = 10;
	node["_terrains"][0]["key"]["_y"] = 11;
	node["_terrains"][0]["value"]["type_"] = 1;
	node["_terrains"][0]["value"]["position_"]["x_"] = 10;
	node["_terrains"][0]["value"]["position_"]["y_"] = 11;

	boardMetaClass->deserialize(&board, node);

	EXPECT_EQ(board.getWidth(), 12);
	EXPECT_EQ(board.getHeight(), 13);
	EXPECT_EQ(board.getTerrains().size(), 1);
}