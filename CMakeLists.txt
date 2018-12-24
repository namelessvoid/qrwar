cmake_minimum_required(VERSION 2.8)
project(QuadRuledWar)

# options
option(BUILD_TESTS "If set to true, tests will build as well" ON)

# set cmake stuff
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${QuadRuledWar_SOURCE_DIR}/cmake/Modules)

set(CMAKE_CXX_FLAGS "-g")
#add_definitions("-Wall")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# SFML
if(WIN32)
  set(SFML_DIR ${CMAKE_SOURCE_DIR}/thirdparty/src/SFML/lib/cmake/SFML)
endif(WIN32)

add_subdirectory(src)

if(BUILD_TESTS)
  add_subdirectory(test)
endif(BUILD_TESTS)
