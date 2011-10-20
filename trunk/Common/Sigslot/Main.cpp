#include <iostream>
#include "sigslot.h"

using namespace std;

class FeedSession 
{
public:
  sigslot::signal0<> SignalSetAllReplyRead;

  void Fun()
  {
    cout<<"Fun"<<endl;
    SignalSetAllReplyRead();
  }
};

class B:public sigslot::has_slots<>
{
public:
  void outerFun()
  {
    cout<<"B outerFun"<<endl;
  }

  void BFun()
  {
    FeedSession f;
    f.SignalSetAllReplyRead.connect(this,&B::outerFun);
    f.Fun();
  }
};


int main()
{
  B b;
  b.BFun();
  return 0;
}