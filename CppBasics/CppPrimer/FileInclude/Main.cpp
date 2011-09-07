#include "Math.h"
#include <iostream>
#include "Math.h"
#include <vector>

using namespace std;

int main()
{
	CMath math;
	//CMath *object = new CMath[100];
	//delete[] object;
	int result = math.Add(1,2);
	cout<<result<<endl;
	vector<CMath> v;
	v.push_back(CMath());
	cout<<"push_back end"<<endl;
}