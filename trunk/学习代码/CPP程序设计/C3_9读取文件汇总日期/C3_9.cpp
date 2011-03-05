/**************************************************
    汇总文件中25号的天数,后面加*号的记为两天

                 程序设计：杨飞
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
