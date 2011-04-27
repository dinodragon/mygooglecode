#include <iostream>

using namespace std;

int main()
{
	enum Week{Mon, Tue = 2, Wed, Thu=2, Fri,Sat, Sun};
	enum Color{Red=5, Green };
	Week day = Wed;
	//day = (Week)(Tue + Fri);
	//int a = 3;
	//if(a == Wed)
	//	cout<< "ПаµИ" <<endl;
	cout<<day<<endl;
}
