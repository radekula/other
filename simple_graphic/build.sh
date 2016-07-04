#!/bin/bash

reset
g++ `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags freeglut` `pkg-config --libs glu` `pkg-config --libs freeglut` `pkg-config --libs gl` main.cpp -o ru.bin
#./ru.bin
g++ `pkg-config --cflags gl` `pkg-config --cflags glu` `pkg-config --cflags freeglut` `pkg-config --libs glu` `pkg-config --libs freeglut` `pkg-config --libs gl` main2.cpp -o lights.bin
./lights.bin
