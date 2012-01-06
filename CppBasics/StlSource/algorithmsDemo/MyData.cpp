#include "MyData.h"

MyData::MyData(void)
{
}

MyData::MyData(std::string id,std::string title)
{
  this->id_ = id;
  this->title_ = title;
}

MyData::~MyData(void)
{
}


//void Show(const std::vector<MyData> & v)
//{
//  for (std::vector<MyData>::const_iterator it = v.begin();it != v.end();++it)
//  {
//    std::cout<<it->id_<<":"<<it->title_<<std::endl;
//  }
//}