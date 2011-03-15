Option Explicit 
Dim fs,result
Set fs = CreateObject("ATLDemo.MyCalc.1")
'fs.Add 1,2,result
fs.Msg
'调用了Msg方法，但还没有解决返回值的问题，如Add方法不知道如何调用。

