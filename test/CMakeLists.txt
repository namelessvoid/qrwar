add_executable(test
    main.cpp
	engine/boardtest.cpp
	engine/squaretest.cpp
	engine/unittest.cpp
	engine/coordinatestest.cpp
	engine/pathfinding/nodetest.cpp
	engine/pathfinding/pathtest.cpp
	engine/pathfinding/astartest.cpp
	gui/buttongrouptest.cpp
	gui/texturemanagertest.cpp
	config/tilesetprocessortest.cpp
)
target_link_libraries(test ${LIBS} cppunit qrwarlib)
