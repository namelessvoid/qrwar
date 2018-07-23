find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

find_package(GMock REQUIRED)
include_directories(${GMOCK_INCLUDE_DIR})

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

	game/meta/coordinatemetaclass_serialize.cpp
	game/meta/coordinatemetaclass_deserialize.cpp
	game/meta/boardmetaclass_serialize.cpp
	game/meta/boardmetaclass_deserialize.cpp
	game/meta/terrainmetaclass_serialize.cpp
	game/meta/terrainmetaclass_deserialize.cpp
	game/meta/deploymentzonemetaclass_serialize.cpp
	game/meta/deploymentzonemetaclass_deserialize.cpp

	game/states/deploystate_init.cpp
	game/states/mapeditorstate_loadmap.cpp

	game/skirmish/mapvalidator_validate.cpp

	meta/properties/testdoubles.cpp
	meta/properties/stdmapproperty_serialize.cpp
	meta/properties/stdmapproperty_deserialize.cpp)

target_link_libraries(unittest ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} cppunit pthread qrwarlib)
