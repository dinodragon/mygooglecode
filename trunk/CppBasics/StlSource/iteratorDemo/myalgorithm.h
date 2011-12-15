#ifndef __MYALGORITHM_H__
#define __MYALGORITHM_H__

namespace yf {

template<typename T>
bool operator==(const ListItem<T> & item,T value)
{
  return item.value() == value;
}

template<typename ITER,typename T>
ITER find(ITER begin,ITER end,T value)
{
  ITER it = begin;
  for (;it != end;++it)
  {
    if ((*it) == value)
    {
      return it;
    }
  }
  return end;
}

} // yf

#endif // __MYALGORITHM_H__