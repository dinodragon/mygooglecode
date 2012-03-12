'变量声明
Dim array1(100) '①100表示该文件夹最多的文件数，如果文件数大于100请自行修改
Dim source(100) '①100表示该文件夹最多的文件数，如果文件数大于100请自行修改
Dim destination(100) '①100表示该文件夹最多的文件数，如果文件数大于100请自行修改

'变量定义
Set fs = CreateObject("Scripting.FileSystemObject")
Set f = fs.GetFolder("F:\转换\") '②此处表示doc所在的文件夹，请根据需要自行修改
Set fc = f.Files

'
i = 0
For Each f1 In fc
    array1(i) = f1.Name
    Ext = fs.GetExtensionName(array1(i))
    Ext = LCase(Ext)
    If Ext = "doc" Then '③此处表示转换类型
        source(i) = f & "\" & array1(i)
        destination(i) = Left(source(i), Len(source(i)) - 4) & ".docx"
        Set wordApp = CreateObject("Word.Application")
        Set wordDoc = wordApp.Documents.Open(source(i))
	wordDoc.convert
        wordDoc.SaveAs destination(i), 16
        wordDoc.Close
        Set wordDoc = Nothing
        wordApp.Quit
        Set wordApp = Nothing
    End If
    i = i + 1
Next
