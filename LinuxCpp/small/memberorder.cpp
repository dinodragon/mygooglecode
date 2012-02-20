
//验证类成员在内存中的布局。
//深入解析C++对象模型中的一个问题。类中相同区段public,protected,private成员是否会在内存中合并存储。
//验证结果，不会合并，直接按定义时的顺序存储。

#include <iostream>

class A
{
public:
  int pu_a;
protected:
  int protected_a;
private:
  int private_a;
private:
  int private_b;
protected:
  int protected_b;
public:
  int pu_b;
  void show()
  {
    std::cout<<&pu_a<<std::endl;
    std::cout<<&protected_a<<std::endl;
    std::cout<<&private_a<<std::endl;
    std::cout<<&private_b<<std::endl;
    std::cout<<&protected_b<<std::endl;
    std::cout<<&pu_b<<std::endl;  }
};

int main()
{
  A a;
  a.show();
	return 0;
}

