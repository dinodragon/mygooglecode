CC = g++
mainapp:outa.o
	${CC} -o outexe outa.o
outa.o:main.cpp
	${CC} -c -o outa.o -host=i686 main.cpp
clean:
	rm -f out*

