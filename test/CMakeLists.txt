add_executable(unittest
    main.cpp
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
