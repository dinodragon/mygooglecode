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
void arrayInsert(T*a,T*s,long size)    //�������������
{
	for(long i=0;i<10;i++)
	{
		for(long k=0;k<size;k++)
		{
			a[k]=s[k];  
		}
	}
}

template<typename T>
void vectorInsert( vector<T> *v,T*s,long size)     //��������������
{
	for(int i=0;i<10;i++)
	{
		for(long k=0;k<size;k++)
		{
			v->push_back(s[k]); 
		}
		//cout<<"capacity:"<<v->capacity()<<"\tsize:"<<v->size()<<endl;
	}
}
template<typename T>
void listInsert(list<T>*l,T*s,long size)   //����������
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
void multisetInsert(multiset<T>*s1,T*s,long size)   //����ؼ��ϲ�������
{
	for(int i=0;i<10;i++)
	{
		for(long k=0;k<size;k++)
		{
			s1->insert(s[k]);   
		}
	}
}
int* genIntData(long size)                  //���������
{
	int* data=new int[size];
	generate(&data[0],&data[size],rand);
	return data;

}   
int main(void)
{
	const long size=100000;
	int* s_data;
	double begin,end;
	s_data=genIntData(size);

	//����
	cout<<"��ʼ����"<<size<<"���������"<<endl;
	begin=(double)clock()/CLK_TCK;
	int array1[size];
	arrayInsert<int>(array1,s_data,size);
	end=(double)clock()/CLK_TCK;
	cout<<"����:"<<(end-begin)<<"��"<<endl;
	
	//����
	begin=(double)clock()/CLK_TCK;
	vector<int> vector1;
	//vector1.reserve(size * 10);
	vectorInsert<int>(&vector1,s_data,size);
	end=(double)clock()/CLK_TCK;
	cout<<"����:"<<(end-begin)<<"��"<<endl;

	//��
	begin=(double)clock()/CLK_TCK;
	list<int> list1;
	listInsert<int>(&list1,s_data,size);
	end=(double)clock()/CLK_TCK;
	cout<<"List:"<<(end-begin)<<"��"<<endl;

	//���ؼ���
	begin=(double)clock()/CLK_TCK;
	multiset<int> multiset1;
	multisetInsert<int>(&multiset1,s_data,size);
	end=(double)clock()/CLK_TCK;
	cout<<"multiset:"<<(end-begin)<<"��"<<endl;

	free(s_data);
	return 0;       
}
