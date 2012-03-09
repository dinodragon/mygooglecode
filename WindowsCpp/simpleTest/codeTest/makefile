CC = cl.exe /c
LINK = link.exe
AddLib = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"

mainexe.exe:main.obj
	$(LINK) /out:mainexe.exe main.obj $(AddLib)
main.obj:main.cpp
	$(CC) main.cpp
clean:
	del *.obj
