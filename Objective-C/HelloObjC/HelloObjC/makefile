CC = gcc -DCLANG_ENABLE_OBJC_ARC=YES
mainexe:YFPoint2D.o YFPoint3D.o YFRectangle.o main.o
	${CC} -o mainexe -framework Cocoa main.o YFPoint2D.o YFPoint3D.o YFRectangle.o
YFPoint2D.o:YFPoint2D.m YFPoint2D.h
	${CC} -c YFPoint2D.m
YFPoint3D.o:YFPoint3D.m YFPoint3D.h
	${CC} -c YFPoint3D.m
YFRectangle.o:YFRectangle.m YFRectangle.h
	${CC} -c YFRectangle.m
main.o:main.m
	${CC} -c main.m
clean:
	rm -f *.o
