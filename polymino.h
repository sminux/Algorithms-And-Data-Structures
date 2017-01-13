#include "AllIn.h"
#include "f.h"

#pragma once

class polymino 
{
private:

	int n;

	f *figures;

	f result;

	size_t colums, rows;

	string hint;

public:
	~polymino(void);

	polymino(f *figures, int n);

	bool equivalent(size_t **first, size_t ** second, int r, int c);

	void backFigure(size_t **figure, size_t **figure_p, int r1, int c1, int r2, int c2);

	size_t **searchEmpty(size_t **first_figure, int r1, int c1, size_t ** second_figure, int r2, int c2);

	f mergeFigures(f first_figure, int r1, int c1, f second_figure, int r2, int c2);

	void compare();

	int poligon();

	void resultFile();
};


