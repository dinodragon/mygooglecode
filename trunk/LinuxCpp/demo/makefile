mainexe:MyClass.o main.o
	g++ -o mainexe MyClass.o main.o
MyClass.o:MyClass.cpp MyClass.h
	g++ -c MyClass.cpp
main.o:main.cpp
	g++ -c main.cpp
clean:
	rm MyClass.o main.o
