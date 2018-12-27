![travis build status badge](https://travis-ci.org/namelessvoid/qrwar.svg?branch=master)

# Introduction

Quad Ruled War (qrw) is a turn based strategy game taking place on a board seperated into squares much like chess. The goal was to produce a minimalistic game for short and fast battles. It only supports hot seat modus for two players on one machine.


# Game

## Skirmish

The game has a single game mode "skirmish" in which to players compete in a hot-seat match against each other. At first, units are deployed in the marked areas known as deployment zones. Afterwards, the the turn-based battle begins and both move and attack until all units of one player have been eliminated.

## Mapeditor

The map editor is used to create new maps for the skirmish game mode. Terrain, structures and deployment zones can be placed and erased by the tools on the right. To grant access to walls, stairs have to be placed on adjacent tiles. To rotate stairs, right click them.


# Building

The game can be build via cmake.

**Dependencies**

- CMake (>= 3.0)
- SFML (>= 2.5)
- TinyXML2 (>= 7.0)
- yaml-cpp (>= 0.6.2)
- CppUnit (for tests)
- gtest & gmock (for tests)

Note that versions are taken from my Arch Linux - lower versions may work as well but have not been tested.

**Configuration**

The build can be configured via these CMake variables:

- `BUILD_TESTS`: If set to `OFF`, the test project will not be included in the build. Default: `ON`

**Installation**

Installation is not yet supported.

## Linux

`mkdir build && cd build && cmake .. && make` should do the trick.

Run the game from the root directory: `./bin/qrwar`

For detailed instructions you can have a look at the Dockerfiles locatet at `ci/`.
There you also find build steps for manually building some thirdparty dependencies.
Note, however, that they also pull in optional dependencies only required for executing tests within a docker container.

If you've got any problems building the game feel free to create an issue.

## Windows

You have to have Visual Studio 2017 installed. At the moment, only 64-bit systems are supported.

Building consists of two steps: 1. Build thirdparty dependencies; 2. Build the game.

**Build Thirdparty Dependencies**

SFML, tinyxml2 and yaml-cpp are included as a separate cmake project located in `thirdparty` which pulls the source (or precompiled binaries) and builds them.

1. Open CLI (e.g. git bash) and navigate to `thirdparty` within the source directory
2. Create and enter build directory: `mkdir build && cd build`
3. Generate solution: `cmake -G "Visual Studio 15 2017 Win64" ..`
4. Build the dependencies: `cmake --build . --config Debug` (alternatively use `--config Release`)

**Build the Game**

After building the thirdparty dependencies, the game can be built similarily:

1. Open CLI (e.g. git bash) and navigate to source directory
2. Create and enter build directory: `mkdir build && cd build`
3. Generate solution: `cmake -G "Visual Studio 15 2017 Win64" ..`
5. Build: `cmake --build . --config Debug` (alternatviely use `--config Release`)

**Run the game**

1. Open CLI (e.g. git bash) and naviate to source directory
2. Call `bin\Debug\qrwar.exe` (or `bin\Release\qrwar.exe`)


# Third party resources

- [Knightsquest.ttf](http://moorstation.org/typoasis/designers/graham/fonts/knightsq.zip)

  True Type Font by [GemFonts](http://moorstation.org/typoasis/designers/gemnew/home.html). See the .zip file for further information.
