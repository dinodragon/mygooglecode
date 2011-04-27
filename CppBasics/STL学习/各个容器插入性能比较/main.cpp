#include<iostream>
#include<iterator>
#include<vector>
#include<list>
#include<set>
#include<time.h>
#include<conio.h>
#include<algorithm>
using namespace std;
template<typename T>
void arrayInsert(T*a,T*s,long size)    //向数组插入数据
{
	//for(long i=0;i<10;i++)  // //好像数组支持不到100万，我们就算10万的
	//最后在把把结果乘以10吧，
	//{
	for(long k=0;k<size;k++)
	{
		a[k]=s[k];  
	}
	//}
}
template<typename T>
void vectorInsert( vector<T> *v,T*s,long size)     //向向量插入数据
{
	for(int i=0;i<10;i++)
	{
		for(long k=0;k<size;k++)
		{
			v->push_back(s[k]); 
		}
	}
}
template<typename T>
void listInsert(list<T>*l,T*s,long size)   //向表插入数据
{
	for(int i=0;i<10;i++)
	{
		for(long k=0;k<size;k++)
		{
			l->push_back(s[k]);
		}   
	}
}
template<class T>
void multisetInsert(multiset<T>*s1,T*s,long size)   //向多重集合插入数据
{
	for(int i=0;i<10;i++)
	{
		for(long k=0;k<size;k++)
		{
			s1->insert(s[k]);   
		}
	}
}
int* genIntData(long size)                  //生成随机数
{
	int* data=new int[size];
	generate(&data[0],&data[size],rand);
	return data;

}   
int main(void)
{
	const long size=100000;
	int* s_data,array1[size];
	double begin,end;
	s_data=genIntData(size);
	vector<int> vector1;
	list<int> list1;
	multiset<int> multiset1;

	//数组
	cout<<"开始插入"<<size<<"个随机整数"<<endl;
	begin=(double)clock()/CLK_TCK;
	arrayInsert<int>(array1,s_data,size);
	end=(double)clock()/CLK_TCK;
	cout<<"数组:"<<(end-begin)<<"秒"<<endl;
	
	//向量
	begin=(double)clock()/CLK_TCK;
	vectorInsert<int>(&vector1,s_data,size);
	end=(double)clock()/CLK_TCK;
	cout<<"向量:"<<(end-begin)<<"秒"<<endl;

	//表
	begin=(double)clock()/CLK_TCK;
	listInsert<int>(&list1,s_data,size);
	end=(double)clock()/CLK_TCK;
	cout<<"List:"<<(end-begin)<<"秒"<<endl;

	//多重集合
	begin=(double)clock()/CLK_TCK;
	multisetInsert<int>(&multiset1,s_data,size);
	end=(double)clock()/CLK_TCK;
	cout<<"集合"<<(end-begin)<<"秒"<<endl;

	free(s_data);
	return 0;       
}
