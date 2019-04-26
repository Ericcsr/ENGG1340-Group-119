word.o:word.cpp word.h
	g++ -pedantic-errors -std=c++11 -c word.cpp
fiomanip.o:fiomanip.cpp fiomanip.h
	g++ -pedantic-errors -std=c++11 -c fiomanip.cpp
screenplay.o:screenplay.cpp screenplay.h
	g++ -pedantic-errors -std=c++11 -c screenplay.cpp
kernel.o:kernel.cpp kernel.h word.h fiomanip.h screenplay.h
	g++ -pedantic-errors -std=c++11 -c kernel.cpp
Kernel: kernel.o screenplay.o fiomanip.o word.o
	g++ -pedantic-errors -std=c++11 kernel.o screenplay.o fiomanip.o word.o -o Kernel
run:
	./Kernel
