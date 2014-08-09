cmake_minimum_required(VERSION 2.8)
project(QuadRuledWar)

# set cmake stuff
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${QuadRuledWar_SOURCE_DIR}/cmake/Modules)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(EXECUTABLE_OUTPUT_PATH bin)

# extern libraries
find_package(SFML 2.0 REQUIRED graphics system window audio)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIRS})
	set(LIBS ${LIBS} ${SFML_LIBRARIES})
endif(SFML_FOUND)

find_package(SFGUI REQUIRED)
if(SFGUI_FOUND)
	include_directories(${SFML_INCLUDE_DIRS})
	set(LIBS ${LIBS} ${SFGUI_LIBRARY})
endif(SFGUI_FOUND)

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
file(GLOB_RECURSE ide_files RELATIVE ${QuadRuledWar_SOURCE_DIR}
	# glob expressions
	${QuadRuledWar_SOURCE_DIR}/include/*.hpp
	${QuadRuledWar_SOURCE_DIR}/res/*
)
add_custom_target(QuadRuledWar SOURCES ${ide_files})
