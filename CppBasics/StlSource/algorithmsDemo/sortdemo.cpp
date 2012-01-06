#include <iostream>
#include <vector>
#include <algorithm>
#include "MyData.h"



void SortTest()
{
  //根据Mydata中的Id字段排序
  std::vector<MyData> v1;
  v1.push_back(MyData("2","two"));
  v1.push_back(MyData("1","one"));
  v1.push_back(MyData("3","three"));
  ShowMyData(v1.begin(),v1.end());
  std::sort(v1.begin(),v1.end(),DataCompare);
  std::cout<<"after sort:"<<std::endl<<std::endl;
  ShowMyData(v1.begin(),v1.end());
}