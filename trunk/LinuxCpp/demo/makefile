CC = g++
mainexe:MyClass.o main.o
	${CC} -o mainexe MyClass.o main.o
MyClass.o:MyClass.cpp MyClass.h
	${CC} -c MyClass.cpp
main.o:main.cpp
	${CC} -c main.cpp
clean:
	rm -f *.o
