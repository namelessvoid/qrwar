#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <gtest/gtest.h>

#include "meta/metamanager.hpp"

#include "game/meta/terrainmetaclass.hpp"
#include "game/meta/boardmetaclass.hpp"
#include "game/meta/coordinatemetaclass.hpp"

#include "engine/terrain.hpp"
#include "engine/board.hpp"

// Return 0 if tests failed.
int runCppUnit()
{
    // Get reference to all registered test methodes.
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    // Create testrunner, add registered methodes and run them.
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(registry.makeTest());
    return runner.run();
}

// Return 0 if tests failed.
int runGtest(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

void registerMetaClasses()
{
    qrw::MetaManager::registerMetaClass<qrw::TerrainMetaClass>(qrw::Terrain::typeName);
    qrw::MetaManager::registerMetaClass<qrw::BoardMetaClass>(qrw::Board::typeName);
    qrw::MetaManager::registerMetaClass<qrw::CoordinateMetaClass>(qrw::Coordinates::typeName);
}

int main(int argc, char* argv[])
{
	registerMetaClasses();

    return runCppUnit() && runGtest(argc, argv);
}
