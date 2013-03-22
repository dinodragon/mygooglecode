CC = g++
app:outa.o
	${CC} -o app outa.o
outa.o:source.cpp
	${CC} -c -o outa.o -host=i686 source.cpp
clean:
	rm -f out*
	rm -f app

