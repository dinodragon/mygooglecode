'��������
Dim array1(100) '��100��ʾ���ļ��������ļ���������ļ�������100�������޸�
Dim source(100) '��100��ʾ���ļ��������ļ���������ļ�������100�������޸�
Dim destination(100) '��100��ʾ���ļ��������ļ���������ļ�������100�������޸�

'��������
Set fs = CreateObject("Scripting.FileSystemObject")
Set f = fs.GetFolder("F:\ת��\") '�ڴ˴���ʾdoc���ڵ��ļ��У��������Ҫ�����޸�
Set fc = f.Files

'
i = 0
For Each f1 In fc
    array1(i) = f1.Name
    Ext = fs.GetExtensionName(array1(i))
    Ext = LCase(Ext)
    If Ext = "doc" Then '�۴˴���ʾת������
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
