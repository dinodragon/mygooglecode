#include <iostream>
#include "Sudoku.h"

using namespace std;

void main()
{
	CSudoku sudoku;
	NUM num[9][9] = 
	{
		8,0,7, 0,0,0, 0,2,4,
		4,5,0, 0,0,0, 0,0,0,
		0,1,0, 5,2,0, 0,0,0,

		0,6,0, 0,9,0, 0,0,0,
		7,0,1, 8,0,6, 2,9,0,
		0,0,0, 0,0,7, 0,0,3,

		0,0,0, 2,0,8, 0,0,6,
		0,2,6, 0,0,0, 8,5,0,
		0,0,0, 0,0,0, 9,0,2
	};
	/**-----------------------------------------------*
		|    8    3    7|    9    6    1|    5    2    4|
		|    4    5    2|    7    8    3|    1    6    9|
		|    6    1    9|    5    2    4|    3    7    8|
		|---------------+---------------+---------------|
		|    5    6    3|    4    9    2|    7    8    1|
		|    7    4    1|    8    3    6|    2    9    5|
		|    2    9    8|    1    5    7|    6    4    3|
		|---------------+---------------+---------------|
		|    9    7    5|    2    1    8|    4    3    6|
		|    1    2    6|    3    4    9|    8    5    7|
		|    3    8    4|    6    7    5|    9    1    2|
		*-----------------------------------------------**/
	if(sudoku.init(num))
		sudoku.display();
	else
		cout<<"��ʼֵ����!"<<endl;
	if (sudoku.cale())
	{
		cout<<"********************************************************"<<endl;
		sudoku.display();
	}
	else
		cout<<"�޽�!"<<endl;


}

//NUM num[9][9] = 
//{
//	0,2,0, 6,4,0, 0,0,0,
//	0,0,0, 0,8,0, 7,0,1,
//	5,0,3, 0,0,0, 0,0,0,
//
//	0,9,0, 3,0,5, 0,6,0,
//	0,0,5, 7,0,4, 0,0,9,
//	0,7,6, 8,0,1, 3,0,2,
//
//	0,1,8, 4,7,2, 0,9,0,
//	0,4,0, 1,5,6, 2,3,8,
//	6,5,2, 0,3,0, 1,7,0
//};