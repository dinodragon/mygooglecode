CC = cl.exe /c
LINK = link.exe /ENTRY:"wWinMainCRTStartup"
AddLib = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"

base64.exe:Base64.obj Base64Dlg.obj Base64Helper.obj stdafx.obj
	$(LINK) /out:base64.exe Base64.obj Base64Dlg.obj Base64Helper.obj stdafx.obj $(AddLib)
Base64.obj:Base64.cpp Base64.h Resource.h
	$(CC) Base64.cpp
Base64Dlg.obj:Base64Dlg.cpp Base64Dlg.h Resource.h
	$(CC) Base64Dlg.cpp
Base64Dlg.obj:Base64Helper.cpp Base64Helper.h
	$(CC) Base64Helper.cpp
stdafx.obj:stdafx.cpp stdafx.h Resource.h
	$(CC) stdafx.cpp
clean:
	del *.obj
