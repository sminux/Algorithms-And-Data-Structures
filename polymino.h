#include "AllIn.h"
#include "f.h"

#pragma once

class polymino 
{
private:
	int n;
	f *figures;
	size_t **solvation;
	size_t colums, rows;
public:
	~polymino(void);
	polymino(f *figures, int n);
	bool checkSquare(int *arrOfSquares);
	void print();
};


