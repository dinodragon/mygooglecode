#include <boost/lexical_cast.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>

void lexicalCast()
{
  using boost::lexical_cast;
  int a = lexical_cast<int>("123");   
  double b = lexical_cast<double>("123.12");   
  std::cout<<a<<std::endl;
  std::cout<<b<<std::endl;
}

void multiplyNumber()
{
  using namespace boost::lambda;
  typedef std::istream_iterator<int> in;

  std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " " );
}

void show(std::map<int,std::string>::value_type item)
{ 
  std::cout<<item.first<<" "<<item.second<<std::endl;
} 

void mapTraversing()
{
  using namespace std;
  std::map<int,std::string> myMap;
  myMap[0] = "a";
  myMap[1] = "b";
  for_each(myMap.begin(),myMap.end(),show);
}

int main()
{   
  //lexicalCast();
  //multiplyNumber();
  mapTraversing();
  return 0;
}

