cmake_minimum_required(VERSION 2.6)
project(QuadRuledWar)
set(CMAKE_BUILD_TYPE Debug)

find_package(SFML REQUIRED)
find_package(SFGUI REQUIRED)

SET(CMAKE_CXX_FLAGS "-std=c++11")

set(LIBS ${LIBS} sfml-graphics sfml-system sfml-window sfml-audio sfgui)

set(COMMON_SOURCE
	src/engine/engine.cpp
	src/engine/board.cpp
	src/engine/square.cpp
	src/engine/terrain.cpp
	src/engine/unit.cpp
	src/engine/player.cpp
	src/gui/texturemanager.cpp
)

set(GUI_SOURCE
	src/tostring.cpp
	src/gui/splashscreen.cpp
	src/gui/imagemanager.cpp
	src/gui/guihandler.cpp
	src/gui/mainwindow.cpp
	src/gui/startgamewindow.cpp
	src/gui/ingamewindow.cpp
	src/gui/placeunitwindow.cpp
	src/gui/boardrenderer.cpp
	src/gui/cursor.cpp
	src/gui/button.cpp
)

include_directories(
	./include
)

set(EXECUTABLE_OUTPUT_PATH ./bin)
add_executable(qrwar src/main.cpp ${COMMON_SOURCE} ${GUI_SOURCE})
target_link_libraries(qrwar ${LIBS})

# Unittest target
set(UNITTEST_SOURCE
	test/engine/boardtest.cpp
	test/engine/squaretest.cpp
	test/engine/unittest.cpp
)

add_executable(test test/main.cpp ${COMMON_SOURCE} ${UNITTEST_SOURCE})
target_link_libraries(test ${LIBS} cppunit)
