space-invaders
==============

space-invaders

#Dependecies
Debian:
sudo apt-get update
sudo apt-get install cmake libncurses-dev 

#Install instructions
Project must be built using CMake
```bash
mkdir bin
cd bin
cmake ..
make
./Space-Invaders
```

The project can be configured using the following CMake flags:
CMake flag | Values | Effect
--- | --- | ---
IS_DEBUG | `0/1` | Will add debugging symbols and output
IS_SFML | `0/1` | Will be compiled with a GUI or only with a curses interface

Note: For IS_SFML to work you need SFML2.1 installed on your machine, see cmake_modules/Findsfml for more info

#Notes:
Runs best on xfce-terminal / terminator / xterm
Runs worse on Konsole

#TODO:
build essentials

