/**************************************************
    �����ļ���25�ŵ�����,�����*�ŵļ�Ϊ����

                 ������ƣ����
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main()
{
	int count=0;
	string a;
	ifstream ain("abc.txt");
	for(string s;getline(ain,s);)
	{
		istringstream stringin(s);
		stringin>>a;
		stringin>>a;
		if(a=="25"){
			stringin>>a;
			if(a=="*") count+=2;
			else count++;
		}
		else
			stringin>>a;
	}
	cout<<"count:"<<count<<endl;
}
