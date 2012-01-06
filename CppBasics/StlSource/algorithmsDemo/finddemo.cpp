#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include "MyData.h"

bool IsRequird(const MyData & d)
{
  return d.id_ == "3";
}

void FindDemo()
{
  std::vector<MyData> v1;
  v1.push_back(MyData("2","two"));
  v1.push_back(MyData("1","one"));
  v1.push_back(MyData("4","four"));
  v1.push_back(MyData("3","three"));
  std::vector<MyData>::iterator it = std::find_if(v1.begin(),v1.end(),IsRequird);
  //std::vector<MyData>::iterator it = std::find_if(v1.begin(),v1.end(),bind2nd(std::equal_to<std::string>(),"3"));
  if (it == v1.end())
  {
    std::cout<<"Not found!"<<std::endl;
  }
  else
  {
    ShowMyData(it,it + 1);
  }
}
