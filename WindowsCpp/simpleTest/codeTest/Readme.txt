这是个文件编码的测试程序，测试main.cpp不同编码方式，如UTF-8，Unicode，ANSI编码时能否正确输出中文。
使用nmake编译。


验证结论：
char str[] = "中文";
std::cout << sizeof(str) <<std::endl;
输出长度与文件编码无关，无论main.cpp是ANSI、UTF-8、Unicode，输出结果都是5（含结尾0）

定义了UNICODE宏后，输出结果变成6。