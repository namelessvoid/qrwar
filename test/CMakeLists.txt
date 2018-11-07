find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

find_package(GMock REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(unittest
	main.cpp

	core/prioritylist_when_iterating.cpp
	core/prioritylist_contains.cpp
	core/prioritylistiterator_operator_equals.cpp
	core/prioritylist_clear.cpp

	core/logger_log.cpp

	engine/boardtest.cpp
	engine/unittest.cpp
	engine/coordinatestest.cpp
	engine/pathfinding/nodetest.cpp
	engine/pathfinding/pathtest.cpp
	engine/pathfinding/astartest.cpp
	gui/buttongrouptest.cpp
	gui/texturemanagertest.cpp
	config/tilesetprocessortest.cpp

	animation/animation_start.cpp
	animation/animation_animate.cpp
	animation/animation_stop.cpp

	foundation/followrouteanimationcomponent_animate.cpp
	foundation/followrouteanimationcomponent_stop.cpp

	game/skirmish/meta/coordinatemetaclass_serialize.cpp
	game/skirmish/meta/coordinatemetaclass_deserialize.cpp
	game/skirmish/meta/boardmetaclass_serialize.cpp
	game/skirmish/meta/boardmetaclass_deserialize.cpp
	game/skirmish/meta/terrainmetaclass_serialize.cpp
	game/skirmish/meta/terrainmetaclass_deserialize.cpp
	game/skirmish/meta/wallmetaclass_serialize.cpp
	game/skirmish/meta/wallmetaclass_deserialize.cpp
	game/skirmish/meta/stairsmetaclass_serialize.cpp
	game/skirmish/meta/stairsmetaclass_deserialize.cpp
	game/skirmish/meta/deploymentzonemetaclass_serialize.cpp
	game/skirmish/meta/deploymentzonemetaclass_deserialize.cpp

	game/states/deploystate_init.cpp
	game/states/mapeditorstate_loadmap.cpp
	game/states/mapeditorstate_placeterrain.cpp
	game/states/mapeditorstate_placestructure.cpp
	game/states/mapeditorstate_resizeboard.cpp

	game/skirmish/mapvalidator_validate.cpp
	game/skirmish/wallaccessstructurebase_rotate.cpp
	game/skirmish/unitmeleeattackability_canbeexecutedon.cpp
	game/skirmish/pathfinding/boardworldadapter_getneighborlocationsfor.cpp
	game/skirmish/pathfinding/boardworldadapter_isaccessiblefrom.cpp

	meta/properties/testdoubles.cpp
	meta/properties/tproperty_serialize.cpp
	meta/properties/tproperty_deserialize.cpp
	meta/properties/stdmapproperty_serialize.cpp
	meta/properties/stdmapproperty_deserialize.cpp
	meta/properties/tclassproperty_serialize.cpp
	meta/properties/tclassproperty_deserialize.cpp)

target_link_libraries(unittest ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} cppunit pthread qrwarlib)
