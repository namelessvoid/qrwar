#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include <gtest/gtest.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include "rendering/rendersystem.hpp"

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

int main(int argc, char* argv[])
{
	sf::RenderWindow renderWindow;
	qrw::g_renderSystem.startUp(renderWindow);

    return runCppUnit() && runGtest(argc, argv);
}
