#include "AllIn.h"

#pragma once

class f
{
private:
	size_t **data;
	size_t c, r;
public:
	~f(void);
	f(size_t **arr, size_t c_r);
	int square();
	bool checkCorrect();
	void findAngle();
	void rotation90();
	void delZeros();
	void print();
	void res();
};

