#!/usr/bin/env sh

# get the latest sfgui version
cd ../..
git clone https://github.com/TankOs/SFGUI.git
cd SFGUI

# build and install it
cmake . && make && sudo make install

#copy FindSFGUI.cmake
sudo cp cmake/FindSFGUI.cmake /usr/share/cmake-2.8/Modules

cd $TRAVIS_BUILD_DIR