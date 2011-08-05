Option Explicit 
Dim fs,result
result = "asdf"

Set fs = CreateObject("ATLDemo.MyCalc.1")
'fs.Add(1,2)
'fs.Msg
'fs.Echo "bbbbbbb"

Dim a
a = "2342344"
fs.Echo(a)
Dim b
fs.Add 1,2,b
'调用了Msg方法，但还没有解决返回值的问题，如Add方法不知道如何调用。

