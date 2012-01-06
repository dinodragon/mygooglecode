#pragma once
#ifndef _MYDATA_H
#define _MYDATA_H

#include <iostream>
#include <string>
#include <vector>

class MyData
{
public:
  MyData(void);
  MyData(std::string id,std::string title);
  std::string id_;
  std::string title_;
  ~MyData(void);
};

template<typename _RanIt>
void ShowMyData(const _RanIt & it1,const _RanIt & it2)
{
  _RanIt it = it1;
  while (it != it2)
  {
    std::cout<<it->id_<<":"<<it->title_<<std::endl;
    it++;
  }
}

inline bool DataCompare(const MyData & d1,const MyData & d2)
{
  return d1.id_ < d2.id_;
}

#endif
