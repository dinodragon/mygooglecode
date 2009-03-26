#include "Sudoku.h"
#include <iostream>

using namespace std;

CSudoku::CSudoku(void)
{
	for (int x =0;x<9;x++)
	{
		for (int y=0;y<9;y++)
		{
			for (int z=1;z<10;z++)
			{
				grid[x][y][z] = 7;
			}
			grid[x][y][0] = 0;
		}
	}
}

bool CSudoku::setNumber(int x,int y,NUM value)
{
	//ASSERT(x>=0 && x<9 && y>=0 && y<9);
	if (grid[x][y][0]>0) return false;

	for (int i=0;i<9;i++)
	{
		if(
			((grid[i][y][value] & 1) !=1) ||
			((grid[x][i][value] & 2) !=2) ||
			((grid[i/3+x/3*3][i%3+y/3*3][value] & 4) != 4)
		)
		return false;
	}

	grid[x][y][0] = value;
	for (int i=0;i<9;i++)
	{
		grid[i][y][value] -= 1;
		grid[x][i][value] -= 2;
		grid[i/3+x/3*3][i%3+y/3*3][value] -= 4;
	}
	return true;
}

//批量设置数字
bool CSudoku::init(NUM num[][9])
{
	for (int y=0;y<9;y++)
	{
		for (int x=0;x<9;x++)
		{
			if (num[x][y]>0)
			{
				if(!setNumber(y,x,num[x][y]))
					return false;
			}
		}
	}
	return true;
}

//设置只有一个可选值的情况.
bool CSudoku::cale()
{
	bool flag=false;
	do 
	{
		flag=false;
		for (int x=0;x<9;x++)
		{
			for (int y=0;y<9;y++)
			{
				if (grid[x][y][0]==0)  //没有填写的方格
				{
					int sum=0,k=0;
					for (int i=1;i<10;i++)
					{
						if(grid[x][y][i]==7)
						{
							sum++;
							k=i;
						}
					}
					if (sum==1)//只有一个可选值则填写.
					{
						if (!setNumber(x,y,k))	return false;
						flag=true;
					}
				}
			}
		}
	} while (flag);
	return true;
}

//进行循环迭代计算
bool CSudoku::itercale()
{
	for (int x=0;x<9;x++)
	{
		for (int y=0;y<9;y++)
		{
			if ( grid[x][y][0] == 0 )
			{
				int sum=0,k=0;
				for (int i=1;i<10;i++)
				{
					if(grid[x][y][i]==7)
					{
						sum++;
						k=i;
					}
				}
				if (sum==1)//只有一个可选值则填写.
				{
					if (!setNumber(x,y,k))	return false;
					flag=true;
				}
			}
		}
	}
	return true;
}

void CSudoku::display()
{
	for (int y=0; y<27; y++)
	{
		for (int x = 0; x<9; x++)
		{
			for(int z = 1+(y%3)*3; z<4+(y%3)*3;z++ )
				if (grid[x][y/3][0]>0)
				{
					cout<<(int)grid[x][y/3][0];
				} 
				else
				{
					if (grid[x][y/3][z] == 7)
					{
						cout<<z;
					}
					else
					{
						cout<<" ";
					}
					//cout<<(int)grid[x][y/3][z];
					
				}				
			cout<<"  ";
			if (x % 3 ==2)
			{
				cout<<" | ";
			}
		}
		cout<<endl;
		if (y%3==2) cout<<endl;
		if (y%9==8) cout<<"-------------------------------------------------------"<<endl;
	}
}

CSudoku::~CSudoku(void)
{
}