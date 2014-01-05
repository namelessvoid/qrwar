#!/usr/bin/env sh

sudo apt-get install libpthread-stubs0-dev
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libx11-dev
sudo apt-get install libxrandr-dev
sudo apt-get install libfreetype6-dev
sudo apt-get install libglew1.5-dev
sudo apt-get install libjpeg8-dev
sudo apt-get install libsndfile1-dev
sudo apt-get install libopenal-dev

cd ..
git clone https://github.com/LaurentGomila/SFML.git
cd SFML
cmake . && make && sudo make install
