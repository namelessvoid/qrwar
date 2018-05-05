add_executable(unittest
	main.cpp

	core/prioritylist_when_iterating.cpp
	core/prioritylist_contains.cpp
	core/prioritylistiterator_operator_equals.cpp

	engine/boardtest.cpp
	engine/unittest.cpp
	engine/coordinatestest.cpp
	engine/pathfinding/nodetest.cpp
	engine/pathfinding/pathtest.cpp
	engine/pathfinding/astartest.cpp
	gui/buttongrouptest.cpp
	gui/texturemanagertest.cpp
	config/tilesetprocessortest.cpp
)
target_link_libraries(unittest ${LIBS} cppunit qrwarlib)
add_test(
	NAME unittest
	COMMAND unittest
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
