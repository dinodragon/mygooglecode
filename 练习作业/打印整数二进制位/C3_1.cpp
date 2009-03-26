/**************************************************
查看整数在内存中的二进制表示

                 程序设计：杨飞
				 http://yangfei.vicp.cc
***************************************************/

#include <iostream>
#include <string>
using namespace std;

class A;
void f1(A & a);

	class A{
		string name;
	public:
		A(string s){
			name = s;
		}
		void show(){
			cout<<"This is class "<<name<<endl;
		}
	friend void f1(A&);
	};

int main()

{
	int i=-1234567;
	double x=2.0/6;
	double *dp = &x;
	unsigned int *p = reinterpret_cast<unsigned int *>(&i);
	for(int n=31; n>=0; n--)
	{
		cout << ((*p>>n) & 1) ;
		if(n % 8 == 0 && n) cout<<",";
	}
	cout<<endl;


/*	class B{
		string name;
	public:
		void show(){
			cout<<"This is class "<<name<<endl;
		}
	};
*/
	
	A a("A");
	//B b;
	a.show();
	//b.show();
	f1(a);
}

void f1(A &a){
	cout<<a.name<<endl;
	a.name="11232";
	a.show();
}
