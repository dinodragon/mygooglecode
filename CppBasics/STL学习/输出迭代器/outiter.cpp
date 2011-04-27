/*
输出迭代器
输出迭代器缺省只写，通常用于将数据从一个位置拷贝到另一个位置。
由于输出迭代器无法读取对象，因此你不会在任何搜索和其他算法中使用它。
要想读取一个拷贝的值，必须使用另一个输入迭代器（或它的继承迭代器）。

当使用copy()算法的时候，你必须确保目标容器有足够大的空间，或者容器本身是自动扩展的。
*/

#include <iostream>
#include <algorithm>   // Need copy()
#include <vector>      // Need vector

using namespace std;

double darray[10] =
{1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9};

vector<double> vdouble(10);

int main()
{
	vector<double>::iterator outputIterator = vdouble.begin();
	copy(darray, darray + 10, outputIterator);
	while (outputIterator != vdouble.end()) {
		cout << *outputIterator << endl;
		outputIterator++;
	}
	return 0;
}
