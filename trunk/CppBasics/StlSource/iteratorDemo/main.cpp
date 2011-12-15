#include <iostream>
#include <memory>
#include "MyList.h"
#include "myalgorithm.h"

int main()
{
  yf::List<int> a;
  a.insert_front(1);
  a.insert_front(2);
  a.insert_front(4);
  a.display();
  yf::ListIter<yf::ListItem<int>> begin(a.front());
  yf::ListIter<yf::ListItem<int>> end;
  yf::ListIter<yf::ListItem<int>> it;
  it = yf::find(begin,end,2);
  if (it != end)
  {
    std::cout<<(*it).value()<<std::endl;
  }
  else
  {
    std::cout<<"Not found!"<<std::endl;
  }
}