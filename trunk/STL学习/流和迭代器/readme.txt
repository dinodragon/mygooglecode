要学会使用迭代器和容器以及算法，需要学习下面的新技术。

流和迭代器
本书的很多例子程序使用I/O流语句来读写数据。例如：

int value;
cout << "Enter value: ";
cin >> value;
cout << "You entered " << value << endl;
对于迭代器，有另一种方法使用流和标准函数。理解的要点是将输入/输出流作为容器看待。因此，任何接受迭代器参数的算法都可以和流一起工作。 

Listing 4. outstrm.cpp 

#include <iostream.h>
#include <stdlib.h>    // Need random(), srandom()
#include <time.h>      // Need time()
#include <algorithm>   // Need sort(), copy()
#include <vector>      // Need vector
 
using namespace std;
 
void Display(vector<int>& v, const char* s);
 
int main()
{
  // Seed the random number generator
  srandom( time(NULL) );
 
  // Construct vector and fill with random integer values
  vector<int> collection(10);
  for (int i = 0; i < 10; i++)
    collection[i] = random() % 10000;;
 
  // Display, sort, and redisplay
  Display(collection, "Before sorting");
  sort(collection.begin(), collection.end());
  Display(collection, "After sorting");
  return 0;
}
 
// Display label s and contents of integer vector v
void Display(vector<int>& v, const char* s)
{
  cout << endl << s << endl;
  copy(v.begin(), v.end(),
    ostream_iterator<int>(cout, "\t"));
  cout << endl;
}
函数Display()显示了如何使用一个输出流迭代器。下面的语句将容器中的值传输到cout输出流对象中:

copy(v.begin(), v.end(),
  ostream_iterator<int>(cout, "\t"));
第三个参数实例化了ostream_iterator<int>类型，并将它作为copy()函数的输出目标迭代器对象。“\t”字符串是作为分隔符。运行结果：

$ g++ outstrm.cpp
$ ./a.out
Before sorting
677   722   686   238   964   397   251   118   11    312
After sorting
11    118   238   251   312   397   677   686   722   964
这是STL神奇的一面『确实神奇』。为定义输出流迭代器，STL提供了模板类ostream_iterator。这个类的构造函数有两个参数：一个ostream对象和一个string值。因此可以象下面一样简单地创建一个迭代器对象：

ostream_iterator<int>(cout, "\n")
该迭代起可以和任何接受一个输出迭代器的函数一起使用。
