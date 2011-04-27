class Animal
{
protected:
	char name[20];
private:
	int age;
public:
	Animal(const char *);
	Animal();
	void showAge();
	void setAge(int);
	void meow();
	void showName();
};

class Cat:public Animal
{
public:
	Cat(const char *);
	void meow();
	void eatFish();
};