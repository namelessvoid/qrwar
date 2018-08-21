cmake_minimum_required(VERSION 2.8)
project(QuadRuledWar)

# set cmake stuff
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${QuadRuledWar_SOURCE_DIR}/cmake/Modules)
set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_definitions("-Wall")

# extern libraries
find_package(SFML 2 REQUIRED graphics audio)
set(LIBS ${LIBS} sfml-graphics sfml-audio)

find_package(tinyxml2 REQUIRED)
if(TINYXML2_FOUND)
	include_directories(${TINYXML2_INCLUDE_DIR})
	set(LIBS ${LIBS} ${TINYXML2_LIBRARIES})
endif(TINYXML2_FOUND)

find_package(yaml-cpp REQUIRED)
if(yaml-cpp_FOUND)
    include_directories(${YAML_CPP_INCLUDE_DIR})
    set(LIBS ${LIBS} ${YAML_CPP_LIBRARIES})
endif(yaml-cpp_FOUND)

# set include path
include_directories(${QuadRuledWar_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(test)
