Ҫѧ��ʹ�õ������������Լ��㷨����Ҫѧϰ������¼�����

���͵�����
����ĺܶ����ӳ���ʹ��I/O���������д���ݡ����磺

int value;
cout << "Enter value: ";
cin >> value;
cout << "You entered " << value << endl;
���ڵ�����������һ�ַ���ʹ�����ͱ�׼����������Ҫ���ǽ�����/�������Ϊ������������ˣ��κν��ܵ������������㷨�����Ժ���һ������ 

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
����Display()��ʾ�����ʹ��һ����������������������佫�����е�ֵ���䵽cout�����������:

copy(v.begin(), v.end(),
  ostream_iterator<int>(cout, "\t"));
����������ʵ������ostream_iterator<int>���ͣ���������Ϊcopy()���������Ŀ����������󡣡�\t���ַ�������Ϊ�ָ��������н����

$ g++ outstrm.cpp
$ ./a.out
Before sorting
677   722   686   238   964   397   251   118   11    312
After sorting
11    118   238   251   312   397   677   686   722   964
����STL�����һ�桺ȷʵ���桻��Ϊ�����������������STL�ṩ��ģ����ostream_iterator�������Ĺ��캯��������������һ��ostream�����һ��stringֵ����˿���������һ���򵥵ش���һ������������

ostream_iterator<int>(cout, "\n")
�õ�������Ժ��κν���һ������������ĺ���һ��ʹ�á�
