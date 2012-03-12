
'创建DOM耗费时间(精确到毫秒)

CreateStartSec = Timer()
Set fs = CreateObject("CmsService.CmsServer")
CreateEndSec = Timer()


'获取DOM耗费时间
GetStartSec = Timer()
pathVar = fs.GetImage("http://172.19.41.114:8080/cms/services/TeamWorkService","25_79574")
GetEndSec = Timer()
MsgBox "获取DOM耗费时间为：" & GetEndSec - GetStartSec & "秒"

GetStartSec = Timer()
pathVar = fs.GetImage("http://172.19.41.114:8080/cms/services/TeamWorkService","25_79574")
pathVar = fs.GetImage("http://172.19.41.114:8080/cms/services/TeamWorkService","25_79574")
pathVar = fs.GetImage("http://172.19.41.114:8080/cms/services/TeamWorkService","25_79574")
pathVar = fs.GetImage("http://172.19.41.114:8080/cms/services/TeamWorkService","25_79575")
GetEndSec = Timer()
MsgBox "获取DOM耗费时间为：" & GetEndSec - GetStartSec & "秒"
