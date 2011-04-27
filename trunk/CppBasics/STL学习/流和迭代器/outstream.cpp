#include <iostream>
#include <stdlib.h>    // Need random(), srandom()
#include <time.h>      // Need time()
#include <algorithm>   // Need sort(), copy()
#include <vector>      // Need vector

using namespace std;

void Display(vector<int>& v, const char* s);

int main()
{
	int size = 100;
	clock_t begin,end;
	srand( (unsigned) time(NULL) );
	// Construct vector and fill with random integer values
	vector<int> collection(size);
	for (int i = 0; i < size; i++)
		collection[i] = rand() % 1000;;

	// Display, sort, and redisplay

	Display(collection, "Before sorting");
	begin = clock();
	sort(collection.begin(), collection.end());
	end = clock();
	Display(collection, "After sorting");

	cout<<"排序使用时间:"<<end-begin<<"毫秒"<<endl;
	return 0;
}

// Display label s and contents of integer vector v
void Display(vector<int>& v, const char* s)
{
	cout << s << endl;
	copy(v.begin(), v.end(),
		ostream_iterator<int>(cout, "\t"));
	cout << endl;
}
