#include "AllIn.h"

#pragma once

class f
{
private:
	int **data;
	int c, r;
public:
	f(int **arr, int cols, int rows);
	~f(void);
	int square();
	void checkCorrect();
	void findAngle();
	void Print();
};

