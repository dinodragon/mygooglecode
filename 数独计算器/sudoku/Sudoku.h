#pragma once

typedef char NUM;

class CSudoku
{
private:
	NUM grid[9][9][10];

public:
	CSudoku(void);
	bool setNumber(int x,int y,NUM value);
	bool init(NUM num[][9]);
	bool cale();
	bool itercale();
	void display();
	~CSudoku(void);
};
