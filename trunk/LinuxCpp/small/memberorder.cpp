
//��֤���Ա���ڴ��еĲ��֡�
//�������C++����ģ���е�һ�����⡣������ͬ����public,protected,private��Ա�Ƿ�����ڴ��кϲ��洢��
//��֤���������ϲ���ֱ�Ӱ�����ʱ��˳��洢��

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

