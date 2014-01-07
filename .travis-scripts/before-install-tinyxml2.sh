#!/usr/bin/env sh

# get the latest tinyxml2 version
cd ../..
git clone https://github.com/leethomason/tinyxml2.git
cd tinyxml2

# build and install
cmake . && make && sudo make install

cd $TRAVIS_BUILD_DIR