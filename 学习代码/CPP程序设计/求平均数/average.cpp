/**************************************************
����������
�ļ��������������ǰ��С���ߴ󣬴�ǰ�ߵ�������ͣ�������Щ�͵�ƽ����

                 ������ƣ����
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