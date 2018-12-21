# Introduction

Quad Ruled War (qrw) is a turn based strategy game taking place on a board seperated into squares much like chess. The goal was to produce a minimalistic game for short and fast battles. It only supports hot seat modus for two players on one machine.

## Building

![travis build status badge](https://travis-ci.org/namelessvoid/qrwar.svg?branch=master)

The source comes with an CMake file and dependes on:

- CMake
- SFML (>= 2.5)
- TinyXML (>= 2.0)
- yaml-cpp 
- CppUnit (for tests)
- gtest & gmock (for tests)

For detailed instructions you can have a look at the Dockerfiles locatet at `ci/`. Note, however, that they also pull in optional dependencies only required for executing tests within a docker container.

If you've got any problems building the game feel free to create an issue.

Note: Installation is not yet supported.

### Windows

Prerequisites:

- Visual Studio 2017
- CMake 3.13.2

Instructions:

1. Open CLI (e.g. git bash) and navigate to source directory
2. Create build directory: `mkdir build64`
3. `cd build64`
4. Generate solution: `cmake -G "Visual Studio 15 2017 Win64"`
5. Build: `cmake --build build64 --config Release`

## Game

### Skirmish

The game has a single game mode "skirmish" in which to players compete in a hot-seat match against each other. At first, units are deployed in the marked areas known as deployment zones. Afterwards, the the turn-based battle begins and both move and attack until all units of one player have been eliminated.

### Mapeditor

The map editor is used to create new maps for the skirmish game mode. Terrain, structures and deployment zones can be placed and erased by the tools on the right. To grant access to walls, stairs have to be placed on adjacent tiles. To rotate stairs, right click them.


## Third party resources

- [Knightsquest.ttf](http://moorstation.org/typoasis/designers/graham/fonts/knightsq.zip)

  True Type Font by [GemFonts](http://moorstation.org/typoasis/designers/gemnew/home.html). See the .zip file for further information.
