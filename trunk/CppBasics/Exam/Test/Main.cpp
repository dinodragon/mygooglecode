#include <iostream>
#include <deque>
#include <vector>
//农夫过河问题
void FarmerProblemEnter();
void PointerTest();

typedef int (*FunType)(void);
std::vector<FunType> FunList;

int main()
{
	FarmerProblemEnter();
	PointerTest();

}