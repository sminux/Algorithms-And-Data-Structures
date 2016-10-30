#include "f.h"

f::f(size_t **arr, size_t c_r)
{
	data = arr;
	c = c_r;
	r = c_r;
}

int f::square()
{
	int S = 0;
	for (size_t i(0); i < r; i++)
	{
		for (size_t j(0); j < c; j++)
			if (data[i][j] == 1) S += 1;
	}
	return S;
}

bool f::checkCorrect()
{
	bool flag = true;
	for (int i(0); i < c-1; i++)
	{
		for (int j(0); j < r - 1; j++)
		{
			if (data[i][j] == 1);
		}
	}
	return flag;
}

void f::delZeros()	//from square matrix to normal
{
	size_t t = 0;
	for (size_t i(0); i < c; i++)
	{
		for (size_t j(0); j < r; j++)
			if (data[i][j] != 0) t += 1;
		if (t == 0)
		{
			for (size_t y = i; y < c - 1; y++)
				for (size_t j(0); j < r; j++)
					data[y][j] = data[y + 1][j];
			c = c - 1;
			i = 0;
		}
		t = 0;
	}

	for (size_t i(0); i < r; i++)
	{
		for (size_t j(0); j < c; j++)
			if (data[i][j] != 0)
				t = 1;
		if (t == 0)
		{
			for (size_t y = i; y < c - 1; y++)
				for (size_t j(0); j<r; j++)
					data[j][y] = data[j][y + 1];
			r = r - 1;
			i = 0;
		}
		t = 0;
	}	
}

void f::rotation90()
{
	int x = 0, y = 0, i;
	for (int j = 0; j<c; j++){
		for (i = r - 1; i >= 0; i--){
			data[y][x++] = data[i][j];
		}; y++; x = 0;
	}
}

void f::print()
{
	cout << endl;
	for (size_t i(0); i < r; i++)
	{
		for (size_t j(0); j < c; j++)
			cout << data[i][j] << ' ';
		cout << endl;
	}
}

void f::res()
{
	ofstream fout("D\\result.txt", ios::out);
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			fout << data[i][j] << ' ';
		}
		cout << endl;
	}
}
f::~f()
{
}
