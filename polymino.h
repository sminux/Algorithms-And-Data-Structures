#include "AllIn.h"
#include "f.h"
#include "f.cpp"

#pragma once

class polymino
{
private:
	int q;
	int r_glob, c_glob;
	int *square;
	size_t **polyArr;
	f *fgr;
public:
	polymino();
	bool checkSquare(int *arrOfSquares, int index);
	void compare(f f1, f f2);
	void packing();
	void result();
	~polymino();
};

