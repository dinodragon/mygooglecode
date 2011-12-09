#include "myallocator.hpp"
#include <iostream>
#include <vector>

using namespace std;

void main()
{
  int ia[5] = {0,1,2,3,4};
  //vector<int,std::allocator<int>> iv(ia,ia+5); //使用标准分配器
  vector<int,yf::allocator<int>> iv(ia,ia+5);
  for (size_t i = 0;i<iv.size();i++)
  {
    cout<<iv[i]<<" ";
  }
  cout<<endl;
}

