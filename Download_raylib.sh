#!/bin/bash

echo "========== Install  raylib for game graphic respresentation ========== "

echo "========== Install packages ========= "
sudo apt install build-essential git libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev libpulse-dev

echo "Clone repository"
git clone https://github.com/raysan5/raylib.git raylib

echo "========== Change folder ========== "
cd raylib/src/

echo "========== Compile library ========== "
make PLATFORM=PLATFORM_DESKTOP # Compiles the library

echo "========== Install library ========== "
sudo make install

cd -
