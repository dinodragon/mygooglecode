#include <iostream>
#include "point.h"

/***********************************************
Point ¿‡∂®“Â
***********************************************/

Point::Point(double xi, double yi){
	number++;
	x=xi;
	y=yi;
}

void Point::show() const{
	std::cout<<"x="<<x<<"\ty="<<y<<std::endl;
}

void Point::showid() const{
	std::cout<<"Number="<<number<<std::endl;
}

void Point::setx(double xi){
	x=xi;
}

void Point::sety(double yi){
	y=yi;
}

double Point::getx(){
	return x;
}

double Point::gety(){
	return y;
}

Point Point::operator*(const Point &a) const{
	Point m(x*a.x,y*a.y);
	return m;
}

Point operator+(const Point& a,const Point& b){
	Point s(a.x+b.x , a.y+b.y);
	return s;
}

int Point::number = 0;