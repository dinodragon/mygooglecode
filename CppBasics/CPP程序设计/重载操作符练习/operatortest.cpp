#include <iostream>
#include <string>
#include "point.h"

using namespace std;

int main(){
	Point a(1.0,2);
	Point b(3,4);
	Point c(5,6);
	a.show();
	(a+b).show();
	(a*b*c*a*b*c).show();
	cout<<a.getx()<<endl;
	a.showid();
}
