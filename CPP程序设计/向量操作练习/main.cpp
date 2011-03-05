#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void main()
{
	vector<int> veci;
	int i;
	ifstream in("data.txt");
	while (in>>i)
	{
		veci.push_back(i);
	}

	for (vector<int>::size_type i=0;i<veci.size();i++)
	{
		cout<<veci[i]<<"\t";
	}

	cout<<endl;

	for (vector<int>::iterator iter = veci.begin();iter != veci.end();iter++)
	{
		cout<<*iter<<"\t";
	}
	cout<<endl;
}