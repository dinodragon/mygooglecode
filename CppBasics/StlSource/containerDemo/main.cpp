#include <ctime>
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <typeinfo>

template<typename T,int Size> void FillData(T& data)
{
  clock_t start = clock();
  for (int i = 0;i < Size;++i)
  {
    data.push(i);
  }
  for (int i = 0;i<Size;++i)
  {
    data.pop();
  }
  clock_t end = clock();
  std::cout << typeid(data).name() << std::endl;
  std::cout << "Fill:"<< Size <<"  ";
  std::cout<< "Waste:" <<end - start<<"ms"<<std::endl;
}

void StackTest()
{
  //不同容器实现的 栈 效率测试
  typedef std::stack<int,std::deque<int>> StackType1; //默认
  StackType1 stack1;
  FillData<StackType1,1000000>(stack1);

  typedef std::stack<int,std::list<int>> StackType2;
  StackType2 stack2;
  FillData<StackType2,1000000>(stack2);

  typedef std::stack<int,std::vector<int>> StackType3;
  StackType3 stack3;
  FillData<StackType3,1000000>(stack3);
}

void QueueTest()
{
  //不同容器实现的 队列 效率测试
  typedef std::queue<int,std::deque<int>> QueueType1; //默认
  QueueType1 queue1;
  FillData<QueueType1,1000000>(queue1);
  
  typedef std::queue<int,std::list<int>> QueueType3;
  QueueType3 queue3;
  FillData<QueueType3,1000000>(queue3);

  //vector不用使用，vector没有pop_front方法
}

int main()
{
  std::cout<<"----Stack---------------"<<std::endl;
  StackTest();
  std::cout<<"----Queue---------------"<<std::endl;
  QueueTest();
}