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
  set(SFML_DIR ${CMAKE_SOURCE_DIR}/thirdparty/SFML/lib/cmake/SFML)
endif(WIN32)

find_package(SFML 2.5 REQUIRED graphics audio)
set(LIBS ${LIBS} sfml-graphics sfml-audio)

# TinyXml2
find_package(tinyxml2 REQUIRED)
if(TINYXML2_FOUND)
	include_directories(${TINYXML2_INCLUDE_DIR})
	set(LIBS ${LIBS} ${TINYXML2_LIBRARIES})
else(TINYXML2_FOUND)
	message(FATAL_ERROR "Required library tinyxml2 could not be found")
endif(TINYXML2_FOUND)

# yaml-cpp
find_package(yaml-cpp REQUIRED)
if(yaml-cpp_FOUND)
    include_directories(${YAML_CPP_INCLUDE_DIR})
    set(LIBS ${LIBS} ${YAML_CPP_LIBRARIES})
endif(yaml-cpp_FOUND)

# c++ file system
set(CXX_FILESYSTEM_LIB
  $<$<CXX_COMPILER_ID:GNU>:stdc++fs>
)
set(LIBS ${LIBS} ${CXX_FILESYSTEM_LIB})

# set include path
include_directories(${QuadRuledWar_SOURCE_DIR}/include)
include_directories(${QuadRuledWar_SOURCE_DIR}/thirdparty/SFML/include)

add_subdirectory(src)

if(BUILD_TESTS)
  add_subdirectory(test)
endif(BUILD_TESTS)
