exefile:Math.o Main.o
	g++ Math.o Main.o -o exefile
Math.o:Math.cpp Math.h
	g++ -c Math.cpp
Main.o:Main.cpp
	g++ -c Main.cpp
clean:
	rm Main.o Math.o