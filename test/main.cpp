#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char* argv[])
{
    // Get reference to all registered test methodes.
    CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
    // Create testrunner, add registered methodes and run them.
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(registry.makeTest());
    return !runner.run();
}