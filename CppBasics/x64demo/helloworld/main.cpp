#include <iostream>

int main()
{
	std::cout<<sizeof(int)<<std::endl;
	std::cout<<sizeof(int*)<<std::endl; //以64位编译时输出为8
}