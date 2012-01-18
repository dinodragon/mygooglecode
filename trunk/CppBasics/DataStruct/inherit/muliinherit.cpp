#include <iostream>

class biology //生物
{
public:
  std::string name;
  int age;
  virtual void show() = 0;
};

class aquatic:virtual public biology  //水生动物
{
public:
  void swim()
  {
    std::cout<<name.c_str()<<" can swim."<<std::endl;
  }

  virtual void show()
  {

  }
};

class terrestrial:virtual public biology  //陆生动物
{
public:
  void run()
  {
    std::cout<<name.c_str()<<" can run."<<std::endl;
  }
  virtual void show()
  {

  }
};

class amphibian:public aquatic,public terrestrial
{
public:
  void swimrun()
  {
    std::cout<<name.c_str()<<" can swim and run."<<std::endl;
  }
  virtual void show()
  {

  }
};

void muliinheritdemo()
{
  std::cout<<"string:"<<sizeof(std::string)<<std::endl;       //32
  std::cout<<"biology:"<<sizeof(biology)<<std::endl;
  std::cout<<"aquatic:"<<sizeof(aquatic)<<std::endl;
  std::cout<<"terrestrial:"<<sizeof(terrestrial)<<std::endl;
  std::cout<<"amphibian:"<<sizeof(amphibian)<<std::endl;
  amphibian frog;//青蛙
  frog.age = 4;
  frog.name = "frog";
  frog.run();
  frog.swim();
  frog.swimrun();
}