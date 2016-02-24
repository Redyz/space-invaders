#!/bin/bash

debug=1
dir=$PWD
mkdir -p bin bin-sfml; cd bin; cmake .. -DIS_DEBUG=$debug -DIS_SFML=0 && make -j4; cd ../bin-sfml; cmake .. -DIS_DEBUG=$debug -DIS_SFML=1 && make -j4
cd $dir

