#include <iostream>
#include "sequencetest.h"

int main()
{
  std::cout<<"----Stack---------------"<<std::endl;
  yf::StackTest();
  std::cout<<"----Queue---------------"<<std::endl;
  yf::QueueTest();
  std::cout<<"----PRIORITY_QUEUE---------------"<<std::endl;
	//debug模式下效率很低
  yf::PropertiQueue();
}