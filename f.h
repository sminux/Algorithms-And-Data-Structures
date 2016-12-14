#include "AllIn.h"

#pragma once

class f
{
public:
	size_t **data;
	size_t c, r;
public:
	~f(void);
	f();
	int **read(string file);
	int get_c();
	int get_r();
	size_t **array();
	int square();
	bool checkCorrect();
	int findAngle();
	void rotation90L();
	void flip();
	void delZeros();
	void print();
	void res();
};

