
'����DOM�ķ�ʱ��(��ȷ������)

CreateStartSec = Timer()
Set fs = CreateObject("CmsService.CmsServer")
CreateEndSec = Timer()


'��ȡDOM�ķ�ʱ��
GetStartSec = Timer()
pathVar = fs.GetImage("http://172.19.41.114:8080/cms/services/TeamWorkService","25_79574")
GetEndSec = Timer()
MsgBox "��ȡDOM�ķ�ʱ��Ϊ��" & GetEndSec - GetStartSec & "��"

GetStartSec = Timer()
pathVar = fs.GetImage("http://172.19.41.114:8080/cms/services/TeamWorkService","25_79574")
pathVar = fs.GetImage("http://172.19.41.114:8080/cms/services/TeamWorkService","25_79574")
pathVar = fs.GetImage("http://172.19.41.114:8080/cms/services/TeamWorkService","25_79574")
pathVar = fs.GetImage("http://172.19.41.114:8080/cms/services/TeamWorkService","25_79575")
GetEndSec = Timer()
MsgBox "��ȡDOM�ķ�ʱ��Ϊ��" & GetEndSec - GetStartSec & "��"
