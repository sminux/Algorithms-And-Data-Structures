#include "AllIn.h"

#pragma once

class f
{
private:
	size_t **data;
	size_t c, r;
public:
	~f(void);
	f();
	int **read(string file);
	int get_c();
	int get_r();
	int square();
	void checkCorrect();
	int findAngle();
	void rotation90R();
	void flip();
	void delZeros();
	void print();
	void res();
};

