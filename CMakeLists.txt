cmake_minimum_required(VERSION 2.6)
project(QuadRuledWar)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} cmake/Modules)

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

SET(CMAKE_CXX_FLAGS "-std=c++11 -g")

set(COMMON_SOURCE
	src/engine/engine.cpp
	src/engine/board.cpp
	src/engine/square.cpp
	src/engine/terrain.cpp
	src/engine/unit.cpp
	src/engine/unitsmap.cpp
	src/engine/army.cpp
	src/engine/player.cpp
	src/gui/texturemanager.cpp
	src/gui/buttongroup.cpp
    src/gui/widget.cpp
	src/gui/button.cpp
	src/gui/signal.cpp
	src/config/xmlhelper.cpp
	src/config/tilesetprocessor.cpp
	src/config/videosettings.cpp
	src/config/audiosettings.cpp
	src/config/settings.cpp
)

set(GUI_SOURCE
	src/tostring.cpp
	src/gui/splashscreen.cpp
	src/gui/imagemanager.cpp
	src/gui/guihandler.cpp
	src/gui/mainwindow.cpp
	src/gui/startgamewindow.cpp
	src/gui/ingamewindow.cpp
	src/gui/boardwidget.cpp
	src/gui/cursor.cpp
	src/gui/radiotogglebutton.cpp
	src/gui/deploywindow.cpp
	src/gui/settingswindow.cpp
	src/gui/window.cpp
	src/gui/animation.cpp
	src/gui/damagenumber.cpp
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
	test/gui/buttongrouptest.cpp
	test/gui/texturemanagertest.cpp
	test/config/tilesetprocessortest.cpp
)

add_executable(test test/main.cpp ${COMMON_SOURCE} ${UNITTEST_SOURCE})
target_link_libraries(test ${LIBS} cppunit)
