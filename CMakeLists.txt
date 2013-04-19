cmake_minimum_required(VERSION 2.6)
project(QuadRuledWar)
set(CMAKE_BUILD_TYPE Debug)

find_package(SFML REQUIRED)
find_package(SFGUI REQUIRED)
set(LIBS ${LIBS} sfml-graphics sfml-system sfml-window sfml-audio sfgui)

set(SOURCE
	src/texturemanager.cpp
	src/engine/engine.cpp
	src/engine/board.cpp
	src/engine/square.cpp
	src/engine/terrain.cpp
	src/engine/unit.cpp
	src/gui/guihandler.cpp
	src/gui/mainwindow.cpp
	src/gui/boardrenderer.cpp
	src/gui/cursor.cpp
)

include_directories(
	./include
)

set(EXECUTABLE_OUTPUT_PATH ./bin)
add_executable(qrwar src/main.cpp ${SOURCE})
target_link_libraries(qrwar ${LIBS})

# Unittest target
set(UNITTEST_SOURCE
	test/engine/boardtest.cpp
	test/engine/squaretest.cpp
)

add_executable(test test/main.cpp ${SOURCE} ${UNITTEST_SOURCE})
target_link_libraries(test ${LIBS} cppunit)
