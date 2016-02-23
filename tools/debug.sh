#!/bin/sh
make -j4; (sleep 3; terminator -e 'sudo cgdb -p `pgrep Space-Invaders`')& ./Space-Invaders
