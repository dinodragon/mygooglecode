#include <iostream>
#include <deque>
#include <vector>
//ũ���������
void FarmerProblemEnter();
void PointerTest();

typedef int (*FunType)(void);
std::vector<FunType> FunList;

int main()
{
	FarmerProblemEnter();
	PointerTest();

}