// crt_begthrdex.cpp
// compile with: /MT
#include <windows.h>
#include <stdio.h>
#include <process.h>

unsigned Counter; 
unsigned __stdcall SecondThreadFunc( void* pArguments )
{
  printf( "In second thread...\n" );

  while ( Counter < 1000000 )
    Counter++;

  _endthreadex( 0 );
  return 0;
} 

class TC
{
public:
  TC():count_(0),stop_(false){}
  unsigned int count_;
  bool stop_;
  static unsigned int __stdcall ThreadFun(void* pArguments)
  {
    TC *p = static_cast<TC *>(pArguments);
    while(p->count_ < 10000000 && !p->stop_)
    {
      p->count_++;
    }
    return p->count_;
  }
};

int main()
{ 
  HANDLE hThread;
  unsigned threadID;

  printf( "Creating second thread...\n" );

  // Create the second thread.
  hThread = (HANDLE)_beginthreadex( NULL, 0, &SecondThreadFunc, NULL, 0, &threadID );

  // Wait until second thread terminates. If you comment out the line
  // below, Counter will not be correct because the thread has not
  // terminated, and Counter most likely has not been incremented to
  // 1000000 yet.
  WaitForSingleObject( hThread, INFINITE );
  printf( "Counter should be 1000000; it is-> %d\n", Counter );
  // Destroy the thread object.
  CloseHandle( hThread );

  //unsigned threadID2;
  //TC t;
  //_beginthreadex(NULL,0,&TC::ThreadFun,&t,0,&threadID2);
  //int in;
  //scanf("%d",&in);
  //printf("%d\r\n",t.count_);
}
