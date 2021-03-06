add_subdirectory(gui/ng)

find_package(tinyxml2 REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

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
	game/skirmish/minimapgenerator.cpp
	game/skirmish/boardbackgroundcomponent.cpp
	game/skirmish/unit.cpp
	game/skirmish/laddercarrier.cpp
	game/skirmish/archer.cpp
	game/skirmish/unitability.cpp
	game/skirmish/unitmovementability.cpp
	game/skirmish/unitmeleeattackability.cpp
	game/skirmish/unitrangeattackability.cpp
	game/skirmish/deployladderability.cpp
	game/skirmish/unitfactory.cpp
	game/skirmish/structure.cpp
	game/skirmish/wallaccessstructurebase.cpp
	game/skirmish/stairs.cpp
	game/skirmish/ladder.cpp
	game/skirmish/wall.cpp
	game/skirmish/structurefactory.cpp
	game/skirmish/structureaccessibilitychecker.cpp
	game/skirmish/coordinates.cpp
	game/skirmish/directions.cpp
	game/skirmish/isometricconversion.cpp
	game/skirmish/boardtoworldconversion.cpp
	game/skirmish/toggleflatmodehandler.cpp

	game/skirmish/gui/victorydialog.cpp
	game/skirmish/gui/mapeditortoolbar.cpp
	game/skirmish/gui/mapselectionwindow.cpp
	game/skirmish/gui/mappreview.cpp
	game/skirmish/gui/skirmishpreparationgui.cpp
	game/skirmish/gui/skirmishpreparationplayeroptions.cpp
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
	meta/metaclass.cpp

	physics/physicsengine.cpp
	physics/texturealphamask.cpp
)

set_target_properties(qrwarlib PROPERTIES OUTPUT_NAME qrwar)
target_link_libraries(qrwarlib
	sfml-audio
	sfml-graphics
	namelessgui
	$<$<CXX_COMPILER_ID:GNU>:stdc++fs>
	tinyxml2
	yaml-cpp
)

add_executable(qrwar main.cpp)
target_link_libraries(qrwar	qrwarlib)
