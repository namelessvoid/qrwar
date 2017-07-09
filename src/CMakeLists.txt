add_subdirectory(gui/ng)

add_library(tostring tostring.cpp)

add_library(qrwarlib
        qrwar.cpp

	config/audiosettings.cpp
	config/settings.cpp
	config/tilesetprocessor.cpp
	config/videosettings.cpp
	config/xmlhelper.cpp

	engine/army.cpp
	engine/board.cpp
	engine/coordinates.cpp
	engine/engine.cpp
	engine/player.cpp
	engine/square.cpp
	engine/terrain.cpp
	engine/unit.cpp
	engine/unitsmap.cpp

	engine/pathfinding/astar.cpp
	engine/pathfinding/node.cpp
	engine/pathfinding/path.cpp

        gamestates/gamestate.cpp
        gamestates/scenestate.cpp
        gamestates/introstate.cpp
        gamestates/mainmenustate.cpp
        gamestates/mapeditorstate.cpp
        gamestates/deploystate.cpp
        gamestates/skirmishstate.cpp

#	gui/animation.cpp
#	gui/boardwidget.cpp
        gui/scene.cpp
        gui/squaremarker.cpp
        gui/cursor.cpp
	gui/terrainentity.cpp
        gui/squaredetailwindow.cpp
#	gui/damagenumber.cpp
#	gui/deploywindow.cpp
#	gui/guihandler.cpp
#	gui/ingamewindow.cpp
#	gui/mainwindow.cpp
#	gui/settingswindow.cpp
#	gui/startgamewindow.cppr
        gui/imagemanager.cpp
	gui/texturemanager.cpp
        gui/guihelper.cpp
)
set_target_properties(qrwarlib PROPERTIES OUTPUT_NAME qrwar)
target_link_libraries(qrwarlib ${LIBS} tostring namelessgui)

add_executable(qrwar main.cpp)
target_link_libraries(qrwar qrwarlib)
