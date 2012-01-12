#include <iostream>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include "MyClass.h"

using namespace std;

void autoPtr()
{
  auto_ptr<string> MyOwnString(new string("This is mine to keep!")); 
  auto_ptr<string> NoItsMine(MyOwnString);

  if (MyOwnString.get() == NULL)
  {
    cout<<"MyOwnString is NULL"<<endl;
  }
  else
  {
    cout << MyOwnString->c_str() << endl;
  }

  if (NoItsMine.get() == NULL)
  {
    cout<<"NoItsMine is NULL"<<endl;
  }
  else
  {
    cout << NoItsMine->c_str() << endl;
  }
}

void shardPtr()
{
  using namespace boost;
  {
    shared_ptr<MyClass> p(new MyClass());
    {
      //只new了一个MyClass，p，p2共同管理该对象
      shared_ptr<MyClass> p2(p);
      p2->Show();
    }//不会析构
    p->Show();
  }//析构
}

void scopedPtr()
{
  using namespace boost;
  scoped_ptr<MyClass> p(new MyClass());
  //forbid to transfer pointer
  //scopedPtr禁止传递,以下语句会错误
  //scoped_ptr<MyClass> p2(p);
  p->Show();
}

boost::shared_ptr<MyClass> sharedPtr_fun()
{
  boost::shared_ptr<MyClass> a(new MyClass());
  return a;
}