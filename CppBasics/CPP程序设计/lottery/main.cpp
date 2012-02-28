#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

//////////////////////////////////////////////////////////////////////////
//帮杨冬冬处理的一个问题，计算大家选中的号码，与中奖号相同的号码个数
//////////////////////////////////////////////////////////////////////////

std::vector<int> split(std::string str,char spliter);

int main()
{
  std::ifstream in("data.txt");
  std::string line;
  int arr[] = {10,57,68,65,82,89,2,71,64,48,19,78,95};
  std::vector<int> right(arr, arr + sizeof(arr)/sizeof(*arr));
  std::sort(right.begin(),right.end());

  std::ofstream out("result.txt");
  while(std::getline(in,line))
  {
    std::cout<<line.c_str()<<std::endl;
    std::string name = line.substr(0,line.find_first_of(' '));
    std::vector<int> numbers = split(line.substr(line.find_first_of(' ') + 1),' ');
    std::vector<int> ok;
    std::set_intersection(right.begin(),right.end(),numbers.begin(),numbers.end(),std::insert_iterator<std::vector<int> >(ok,ok.end()));
    out<<name.c_str()<<" "<<numbers.size()<<" "<<ok.size()<<std::endl;
  }
}

std::vector<int> split(std::string str,char spliter)
{
  std::vector<int> result;
  while(!str.empty())
  {
    std::string data = str.substr(0,str.find_first_of(spliter));
    result.push_back(atoi(data.c_str()));
    size_t t = str.find_first_of(spliter);
    if (str.find_first_of(spliter) != -1)
    {
      str = str.substr(str.find_first_of(spliter) + 1);
    }
    else
    {
      str = "";
    }
  }
  std::sort(result.begin(),result.end());
  return result;
}