#include <iostream>
#include <bitset>
#include <fstream>
#include <time.h>

using namespace std;

int main()
{
	clock_t start = clock();
	bitset<1000000> * p = new bitset<1000000>;
	p->set();
	for(int i=2;i<=1000;++i)
		for(int j=i*i;j< p->size();j+=i)
			p->reset(j);
	ifstream in("in.txt");
	ofstream out("out.txt");
	int data,count=0;

	for(;in>>data;)
	{
		count = 0;
		if(p->test(data))
		{
			for(int i=2;i<=data;i++)
				count += p->test(i);
			out<<count<<endl;
		}	
		else
			out<<0<<endl;
	}
	cout<<"Ö´ÐÐÊ±¼ä:"<<(clock()-start)*1.0/CLK_TCK<<"Ãë"<<endl;

}