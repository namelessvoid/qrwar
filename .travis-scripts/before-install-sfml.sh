#!/usr/bin/env sh

# install dependencies
sudo apt-get install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev

# get the latest sfml version
cd ../..
git clone https://github.com/LaurentGomila/SFML.git
cd SFML

# build and install it
cmake . && make && sudo make install

# copy FindSFML.cmake
sudo cp cmake/Modules/FindSFML.cmake /usr/share/cmake-2.8/Modules

cd $TRAVIS_BUILD_DIR
