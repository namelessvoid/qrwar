#include <gtest/gtest.h>

#include "game/meta/boardmetaclass.hpp"

#include "meta/metamanager.hpp"

#include "engine/board.hpp"

TEST(BoardMetaClass_Serialize, IncludesAllProperties)
{
	qrw::Board board(100, 200);
	const qrw::MetaClass* boardMetaClass = qrw::MetaManager::getMetaClassFor<qrw::Board>();
	YAML::Emitter emitter;

	boardMetaClass->serialize(&board, emitter);

	YAML::Node result = YAML::Load(emitter.c_str());
	ASSERT_TRUE(result["_width"]) << "Key '_width' does not exist";
	ASSERT_TRUE(result["_height"]) << "Key '_height' does not exist";
	EXPECT_EQ(result["_width"].as<unsigned int>(), board.getWidth());
	EXPECT_EQ(result["_height"].as<unsigned int>(), board.getHeight());
}