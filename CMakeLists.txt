cmake_minimum_required(VERSION 2.8)
project(QuadRuledWar)

# set cmake stuff
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${QuadRuledWar_SOURCE_DIR}/cmake/Modules)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_definitions("-Wall")

# extern libraries
find_package(SFML 2 REQUIRED graphics system window audio)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIRS})
	set(LIBS ${LIBS} ${SFML_LIBRARIES})
endif(SFML_FOUND)

find_package(tinyxml2 REQUIRED)
if(TINYXML2_FOUND)
	include_directories(${TINYXML2_INCLUDE_DIR})
	set(LIBS ${LIBS} ${TINYXML2_LIBRARIES})
endif(TINYXML2_FOUND)

# set include path
include_directories(${QuadRuledWar_SOURCE_DIR}/include)

# subdirectory with main code
add_subdirectory(src)
# subdirectory for tests
add_subdirectory(test)

# IDE stuff: Show headers and resources in IDEs like QtCreator or Visual Studio
file(GLOB_RECURSE resource_files RELATIVE ${QuadRuledWar_SOURCE_DIR}
    ${QuadRuledWar_SOURCE_DIR}/res/*
)

add_custom_target(res SOURCES
    ${resource_files}
)

add_custom_target(travis SOURCES
    .travis-scripts/before-install-sfml.sh
    .travis-scripts/before-install-tinyxml2.sh
    .travis.yml
)
