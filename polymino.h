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

	string hint;

public:
	~polymino(void);

	polymino(f *figures, int n);

	void searchEmpty(size_t **first_figure, int r1, int c1, size_t ** second_figure, int r2, int c2);

	size_t **mergeFigures(size_t **first_figure, int r1, int c1, size_t ** second_figure, int r2, int c2);

	void compare();

	int poligon();

	//void poligonVariability();

	void resultFile();
};


