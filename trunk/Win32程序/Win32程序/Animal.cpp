#include <iostream>
#include <string.h>
#include "Animal.h"

using namespace std;

Animal::Animal(const char *name)
{
	strcpy(this->name,name);
}

Animal::Animal()
{
	strcpy(this->name,"noName");
	this->age = 0;
}

void Animal::showAge()
{
	cout<<name<<" is "<<age<<endl;
}

void Animal::setAge(int age)
{
	this->age=age;
}

void Animal::meow()
{
	cout<<"Animal is meow!"<<endl;
}

void Animal::showName()
{
	cout<<name<<endl;
}



void Cat::meow()
{
	cout<<"Cat is meow!"<<endl;
}

void Cat::eatFish()
{
	cout<<"Cat is eating fish!"<<endl;
}

Cat::Cat(const char *name)
{
	strcpy(this->name,name);
}