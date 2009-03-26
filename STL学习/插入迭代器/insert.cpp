//插入迭代器用于将值插入到容器中。它们也叫做适配器，因为它们将容器适配或转化为一个迭代器，
//并用于copy()这样的算法中。例如，一个程序定义了一个链表和一个矢量容器:
//
//list<double> dList;
//vector<double> dVector;
//通过使用front_inserter迭代器对象，可以只用单个copy()语句
//就完成将矢量中的对象插入到链表前端的操作：
//
//copy(dVector.begin(), dVector.end(), front_inserter(dList));
//三种插入迭代器如下：
//
//·        普通插入器 将对象插入到容器任何对象的前面。
//
//·        Front inserters 将对象插入到数据集的前面——例如，链表表头。
//
//·        Back inserters 将对象插入到集合的尾部——例如，矢量的尾部，导致矢量容器扩展。
//
//使用插入迭代器可能导致容器中的其他对象移动位置，因而使得现存的迭代器非法。
//例如，将一个对象插入到矢量容器将导致其他值移动位置以腾出空间。一般来说，
//插入到象链表这样的结构中更为有效，因为它们不会导致其他对象移动。

#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

int iArray[5] = { 1, 2, 3, 4, 5 };

void Display(list<int>& v, const char* s);

int main()
{
	list<int> iList;

	// Copy iArray backwards into iList
	copy(iArray, iArray + 5, front_inserter(iList));
	Display(iList, "Before find and copy");

	// Locate value 3 in iList
	list<int>::iterator p =
		find(iList.begin(), iList.end(), 3);

	// Copy first two iArray values to iList ahead of p
	copy(iArray, iArray + 2, inserter(iList, p));
	Display(iList, "After find and copy");

	return 0;
}

void Display(list<int>& a, const char* s)
{
	cout << s << endl;
	copy(a.begin(), a.end(),
		ostream_iterator<int>(cout, " "));
	cout << endl;
}
