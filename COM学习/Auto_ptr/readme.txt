智能指针详见C++ primer 中文第四版 P591

内存泄露的诊断
//一是包含头文件
#include<crtdbg.h>
//二是在需要检测内存泄漏的地方添加下面这条语句来输出内存泄漏信息：
_CrtDumpMemoryLeaks();