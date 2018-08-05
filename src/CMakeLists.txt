add_subdirectory(gui/ng)

add_library(qrwarlib
	qrwar.cpp

	core/mouse.cpp
	core/logger.cpp

	config/audiosettings.cpp
	config/settings.cpp
	config/tilesetprocessor.cpp
	config/videosettings.cpp
	config/xmlhelper.cpp

	engine/board.cpp
	engine/player.cpp
	engine/terrain.cpp
	engine/unit.cpp

	engine/pathfinding/path.cpp

	rendering/rendersystem.cpp
	rendering/renderable.cpp
	rendering/guicamera.cpp
	rendering/birdseyecamera.cpp

	animation/animationsystem.cpp

	eventsystem/eventsystem.cpp
	eventsystem/inputevents.cpp
	eventsystem/eventhandler.cpp
	eventsystem/sfeventsource.cpp

	foundation/gameobject.cpp
	foundation/gamecomponent.cpp
	foundation/spritecomponent.cpp
	foundation/textcomponent.cpp
	foundation/followrouteanimationcomponent.cpp

	gamestates/gamestate.cpp

	game/states/scenestate.cpp
	game/states/introstate.cpp
	game/states/mainmenustate.cpp
	game/states/mapeditorstate.cpp
	game/states/skirmishpreparationstate.cpp
	game/states/deploystate.cpp
	game/states/skirmishstate.cpp
	game/damagenumber.cpp
	game/events.cpp
	game/deploymentzone.cpp

	game/skirmish/mapmanager.cpp
	game/skirmish/mapvalidator.cpp
	game/skirmish/structure.cpp
	game/skirmish/coordinates.cpp

	game/skirmish/gui/victorydialog.cpp
	game/skirmish/gui/mapeditortoolbar.cpp
	game/skirmish/gui/squaredetailwindow.cpp

	game/skirmish/pathfinding/boardworldadapter.cpp

	game/skirmish/meta/boardmetaclass.cpp
	game/skirmish/meta/terrainmetaclass.cpp
	game/skirmish/meta/structuremetaclass.cpp
	game/skirmish/meta/deploymentzonemetaclass.cpp
	game/skirmish/meta/coordinatemetaclass.cpp

	game/path.cpp
	game/pathrendercomponent.cpp

	game/cameras/skirmishcamera.cpp

	gui/scene.cpp
	gui/squaremarker.cpp
	gui/cursor.cpp
	gui/texturemanager.cpp
	gui/guihelper.cpp

	meta/metamanager.cpp
	meta/metaclass.cpp)
set_target_properties(qrwarlib PROPERTIES OUTPUT_NAME qrwar)
target_link_libraries(qrwarlib ${LIBS} stdc++fs namelessgui)

add_executable(qrwar main.cpp)
target_link_libraries(qrwar qrwarlib)
