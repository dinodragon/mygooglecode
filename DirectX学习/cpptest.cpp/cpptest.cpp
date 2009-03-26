#include <iostream>
#include <math.h>

using namespace std;

typedef struct  
{
	int x;
	int y;
} POINT;

#define mid(a,b) ((a)+(b))/(2.0f)
void main()
{
	POINT b = {100,0}, c = {100,100}; //右下角
	POINT p = {80,100}; //控制点
	POINT x1,x2,x3;


	float k = (c.y-p.y)/float(c.x - p.x); //对称轴的斜率
	
	//对称轴方程 y = -kx+z
	float z = k * (mid(p.x,c.x)) + mid(p.y,c.y);

	x1.y = c.y;
	x1.x = (mid(p.y,c.y) - x1.y)*k + mid(p.x,c.x);
	
	x2.y = b.y;
	x2.x = (mid(p.y,c.y) - x2.y)*k + mid(p.x,c.x);

	x3.x = 2*(k*z-b.x-k*b.y)/(k*k -1) - b.x;
	x3.y = 2*((k*z-b.x-k*b.y)/(1-k) + z) - b.y;

	cout<<"x1("<<x1.x<<","<<x1.y<<")"<<endl;
	cout<<"x2("<<x2.x<<","<<x2.y<<")"<<endl;
	cout<<"x3("<<x3.x<<","<<x3.y<<")"<<endl;
	
}