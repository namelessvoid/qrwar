cmake_minimum_required(VERSION 2.8)
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
	src/engine/coordinates.cpp
	src/engine/pathfinding/path.cpp
	src/engine/pathfinding/astar.cpp
	src/engine/pathfinding/node.cpp
	src/gui/texturemanager.cpp
	src/gui/ng/buttongroup.cpp
	src/gui/ng/widget.cpp
	src/gui/ng/spritewidget.cpp
	src/gui/ng/button.cpp
	src/gui/ng/signal.cpp
	src/config/xmlhelper.cpp
	src/config/tilesetprocessor.cpp
	src/config/videosettings.cpp
	src/config/audiosettings.cpp
	src/config/settings.cpp
	src/gui/ng/label.cpp
)

set(GUI_SOURCE
	src/tostring.cpp
	src/gui/imagemanager.cpp
	src/gui/guihandler.cpp
	src/gui/mainwindow.cpp
	src/gui/startgamewindow.cpp
	src/gui/ingamewindow.cpp
	src/gui/boardwidget.cpp
	src/gui/cursor.cpp
	src/gui/ng/radiotogglebutton.cpp
	src/gui/deploywindow.cpp
	src/gui/settingswindow.cpp
	src/gui/ng/window.cpp
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
	test/engine/coordinatestest.cpp
	test/engine/pathfinding/nodetest.cpp
	test/engine/pathfinding/pathtest.cpp
	test/engine/pathfinding/astartest.cpp
	test/gui/buttongrouptest.cpp
	test/gui/texturemanagertest.cpp
	test/config/tilesetprocessortest.cpp
)

add_executable(test test/main.cpp ${COMMON_SOURCE} ${UNITTEST_SOURCE})
target_link_libraries(test ${LIBS} cppunit)

# IDE stuff: Show header in IDEs like QtCreator or Visual Studio
add_custom_target(QuadRuledWar SOURCES
	# misc
	.gitignore
	res/defaulttileset.xml
	res/defaultguitileset.xml
	res/conf/settings.xml
	res/img/defaultguitileset.png
	res/img/defaulttileset.png
	# header files
	include/engine/engine.hpp
	include/engine/board.hpp
	include/engine/square.hpp
	include/engine/terrain.hpp
	include/engine/unit.hpp
	include/engine/unitsmap.hpp
	include/engine/army.hpp
	include/engine/player.hpp
	include/engine/coordinates.hpp
	include/engine/pathfinding/path.hpp
	include/engine/pathfinding/astar.hpp
	include/engine/pathfinding/node.hpp
	include/gui/texturemanager.hpp
	include/gui/ng/buttongroup.hpp
	include/gui/ng/widget.hpp
	include/gui/ng/spritewidget.hpp
	include/gui/ng/button.hpp
        include/gui/ng/signal.hpp
        include/gui/ng/singleparametersignal.hpp
	include/config/xmlhelper.hpp
	include/config/tilesetprocessor.hpp
	include/config/videosettings.hpp
	include/config/audiosettings.hpp
	include/config/settings.hpp
	include/gui/ng/label.hpp
	include/tostring.hpp
	include/gui/imagemanager.hpp
	include/gui/guihandler.hpp
	include/gui/mainwindow.hpp
	include/gui/startgamewindow.hpp
	include/gui/ingamewindow.hpp
	include/gui/boardwidget.hpp
	include/gui/cursor.hpp
	include/gui/ng/radiotogglebutton.hpp
	include/gui/deploywindow.hpp
	include/gui/settingswindow.hpp
	include/gui/ng/window.hpp
	include/gui/animation.hpp
	include/gui/damagenumber.hpp
)
