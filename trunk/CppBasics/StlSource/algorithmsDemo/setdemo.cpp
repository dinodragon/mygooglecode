#include <iostream>
#include <vector>
#include <algorithm>
#include "MyData.h"

void SetDemo()
{
  //计算两个集合的差
  std::vector<MyData> v1;
  v1.push_back(MyData("2","two"));
  v1.push_back(MyData("1","one1")); //不会使用==比较，这个数据就比较不出来
  v1.push_back(MyData("4","four"));
  v1.push_back(MyData("3","three"));

  std::vector<MyData> v2;
  v2.push_back(MyData("2","two"));
  v2.push_back(MyData("1","one"));
  v2.push_back(MyData("4","four"));

  //只支持对已排序的集合做差集
  std::sort(v1.begin(),v1.end(),DataCompare);
  std::sort(v2.begin(),v2.end(),DataCompare);
  std::vector<MyData> vresult;
  set_difference(v1.begin(),v1.end(),v2.begin(),v2.end(),inserter(vresult,vresult.end()),DataCompare);
  //inserter的使用Demo
  //inserter(vresult,vresult.end()) = MyData("332","23333");
  //即调用container的insert方法。
  ShowMyData(vresult.begin(),vresult.end());
}
