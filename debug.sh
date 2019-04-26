#! /bin/bash debug.sh
g++ -pedantic-errors -std=c++11 -c kernal.cpp word.cpp screenplay.cpp fiomanip.cpp main.cpp
g++ -pedantic-errors -std=c++11 kernal.o word.o screenplay.o fiomanip.o main.o -o main
./main

