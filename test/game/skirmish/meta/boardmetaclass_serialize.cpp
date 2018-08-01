#include <gtest/gtest.h>

#include "game/skirmish/meta/boardmetaclass.hpp"
#include "game/skirmish/meta/coordinatemetaclass.hpp"
#include "game/skirmish/meta/terrainmetaclass.hpp"

#include "meta/metamanager.hpp"

#include "gui/scene.hpp"

#include "engine/board.hpp"
#include "engine/terrain.hpp"
#include "engine/terraintypes.hpp"
#include "game/skirmish/coordinates.hpp"

TEST(BoardMetaClass_Serialize, Then_all_properties_are_included)
{
	qrw::MetaManager metaManager;
	metaManager.registerMetaClass<qrw::BoardMetaClass>(qrw::Board::typeName);
	metaManager.registerMetaClass<qrw::CoordinateMetaClass>(qrw::Coordinates::typeName);
	metaManager.registerMetaClass<qrw::TerrainMetaClass>(qrw::Terrain::typeName);

	qrw::Board board(100, 200);
	board.setTerrain({0, 0}, qrw::Terrain::createTerrain(qrw::TERRAINTYPES::ET_HILL));
	const qrw::MetaClass* boardMetaClass = metaManager.getMetaClassFor<qrw::Board>();
	YAML::Emitter emitter;

	boardMetaClass->serialize(&board, emitter);

	YAML::Node result = YAML::Load(emitter.c_str());
	ASSERT_TRUE(result["_width"]) << "Key '_width' does not exist";
	ASSERT_TRUE(result["_height"]) << "Key '_height' does not exist";
	ASSERT_TRUE(result["_terrains"]) << "Key '_terrains' does not exist";
	EXPECT_EQ(result["_width"].as<unsigned int>(), board.getWidth());
	EXPECT_EQ(result["_height"].as<unsigned int>(), board.getHeight());
	EXPECT_EQ(result["_terrains"].size(), 1);
}