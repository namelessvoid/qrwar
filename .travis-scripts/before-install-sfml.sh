#!/usr/bin/env sh

# install dependencies
sudo apt-get install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libx11-xcb-dev libxcb-image0-dev libxcb-randr0-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev libudev-dev

# get the latest sfml version
cd ../..
git clone https://github.com/LaurentGomila/SFML.git
cd SFML

# build and install it
cmake . && make && sudo make install

# copy FindSFML.cmake
sudo cp cmake/Modules/FindSFML.cmake $TRAVIS_BUILD_DIR/cmake/Modules

cd $TRAVIS_BUILD_DIR
