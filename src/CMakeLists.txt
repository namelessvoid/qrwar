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
	engine/player.cpp
	engine/terrain.cpp
	engine/unit.cpp
	engine/unitsmap.cpp

	engine/pathfinding/astar.cpp
	engine/pathfinding/node.cpp
	engine/pathfinding/path.cpp

        rendering/rendersystem.cpp
        rendering/renderable.cpp

        animation/animationsystem.cpp

        eventsystem/eventsystem.cpp
        eventsystem/eventhandler.cpp
        eventsystem/sfeventsource.cpp

        foundation/gameobject.cpp
        foundation/gamecomponent.cpp
        foundation/spritecomponent.cpp
        foundation/textcomponent.cpp

        gamestates/gamestate.cpp

        game/states/scenestate.cpp
        game/states/introstate.cpp
        game/states/mainmenustate.cpp
        game/states/mapeditorstate.cpp
        game/states/deploystate.cpp
        game/states/skirmishstate.cpp
        game/damagenumber.cpp
        game/gui/victorydialog.cpp

        game/path.cpp
        game/pathrendercomponent.cpp

#	gui/animation.cpp
#	gui/boardwidget.cpp
        gui/scene.cpp
        gui/squaremarker.cpp
        gui/cursor.cpp
        gui/squaredetailwindow.cpp
#	gui/deploywindow.cpp
#	gui/guihandler.cpp
#	gui/ingamewindow.cpp
#	gui/mainwindow.cpp
#	gui/settingswindow.cpp
#	gui/startgamewindow.cpp
        gui/imagemanager.cpp
	gui/texturemanager.cpp
        gui/guihelper.cpp
)
set_target_properties(qrwarlib PROPERTIES OUTPUT_NAME qrwar)
target_link_libraries(qrwarlib ${LIBS} tostring namelessgui)

add_executable(qrwar main.cpp)
target_link_libraries(qrwar qrwarlib)
