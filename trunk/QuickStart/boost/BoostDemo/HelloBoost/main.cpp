#include <boost/lexical_cast.hpp>
#include <iostream>
using boost::lexical_cast;

void lexicalCast()
{
  int a = lexical_cast<int>("123");   
  double b = lexical_cast<double>("123.12");   
  std::cout<<a<<std::endl;
  std::cout<<b<<std::endl;
}


int main()
{   
  lexicalCast();
  return 0;
}

