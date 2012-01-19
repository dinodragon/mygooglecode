CC = cl.exe /c
LINK = link.exe
mainexe.exe:MyClass.obj main.obj
	$(LINK) /out:mainexe.exe MyClass.obj main.obj
MyClass.obj:MyClass.cpp MyClass.h
	$(CC) MyClass.cpp
main.obj:main.cpp
	$(CC) main.cpp
clean:
	del *.obj
