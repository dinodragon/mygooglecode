/**************************************************
问题描述：
文件中有许多整数，前者小后者大，从前者到后者求和，再求这些和的平均数

                 程序设计：杨飞
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	int start,end,count=0,sum=0;
	ifstream fin("data.txt");
	for(string s;getline(fin,s);)
	{
		istringstream sin(s);
		sin>>start>>end;
		sum += (start + end)*(end - start + 1) / 2;
		count++;
	}
	cout<<double(sum)/count<<endl;
	return 0;

}