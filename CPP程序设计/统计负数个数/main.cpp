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
	cout<<"data.txt�ļ���һ����"<<count<<"������"<<endl;
	return -1;
}