#include <iostream>

class A
{
public:
  int age;
  virtual void show()
  {
  };
};


int main()
{
  A b;
  b.age = 1;
  std::cout<<"pointer to object:"<<&b<<std::endl;
  std::cout<<"pointer to first member:"<<&(b.age)<<std::endl;
  std::cout<<"size of object:"<<sizeof(b)<<std::endl;
}
