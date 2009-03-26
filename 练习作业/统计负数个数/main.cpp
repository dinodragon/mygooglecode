#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	int val=0,count=0;
	ifstream in("data.txt");
	while(in>>val)
	{
		if(val<0) count++;
	}
	cout<<"data.txt文件中一共有"<<count<<"个负数"<<endl;
	return -1;
}