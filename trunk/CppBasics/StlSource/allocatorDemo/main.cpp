#include "myallocator.hpp"
#include <iostream>
#include <vector>

using namespace std;

void main()
{
  int ia[5] = {0,1,2,3,4};
  unsigned int i;

  vector<int,yf::allocator<int>> iv(ia,ia+5);
  for (int i = 0;i<iv.size();i++)
  {
    cout<<iv[i]<<" ";
  }
  cout<<endl;
}

