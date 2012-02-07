#include <iostream>

int main()
{
	int a = 12;
	int* p = &a;
	std::cout<<sizeof(int)<<std::endl;
	std::cout<<sizeof(int*)<<std::endl; //以64位编译时输出为8
}