word.o:word.cpp word.h
	g++ -pedantic-errors -std=c++11 -c word.cpp
fiomanip.o:fiomanip.cpp fiomanip.h
	g++ -pedantic-errors -std=c++11 -c fiomanip.cpp
screenplay.o:screenplay.cpp screenplay.h
	g++ -pedantic-errors -std=c++11 -c screenplay.cpp
kernel.o:kernel.cpp kernel.h word.h fiomanip.h screenplay.h
	g++ -pedantic-errors -std=c++11 -c kernel.cpp
main.o:main.cpp main.h
	g++ -pedantic-errors -std=c++11 -c main.cpp
wordmemor:main.o kernel.o fiomanip.o screenplay.o word.o
	g++ -pedantic-errors -std=c++11 main.o kernel.o fiomanip.o screenplay.o word.o -o wordmemor
run:
	./wordmemor
