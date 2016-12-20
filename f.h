#include "AllIn.h"

#pragma once

class f
{
public:
	size_t **data;
	size_t c, r;
	string hint;
public:
	~f(void);
	f();

	f(size_t **data, int r, int c);

	int **read(string file);

	int square();

	int plenum();

	bool checkCorrect();

	void findAngle();

	void rotation90R();

	void rotation90L();

	void flipVerticaly();

	void flipHorizontaly();

	void delZeros();

	void print();

	int get_c();

	int get_r();

	size_t **array();
};

