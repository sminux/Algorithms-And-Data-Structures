#include "f.h"


f::f(int **arr, int cols, int rows)
{
	data = arr;
	c = cols;
	r = rows;
}

int f::square()
{
	int S = 0;
	for (int i(0); i < r; i++)
	{
		for (int j(0); j < c; j++)
			if (data[i][j] == 1) S += 1;
	}
	return S;
}

void f::checkCorrect()
{
	int wall = 0;
	for (int i(0); i < r-1; i++)
	{
		for (int j(0); j < c - 1; j++)
		{
			if ((data[i][j] == 1) && (data[i][j] == data[i + 1][j + 1]))
				if ((data[i + 1][j] == 0) && (data[i][j + 1] == 0))
					cout << "Bad figure :( \t["  << i << "," << j << "]"<< endl;
			if ((data[i][j] == 0) && (data[i][j] == data[i + 1][j + 1]))
				if ((data[i + 1][j] == 1) && (data[i][j + 1] == 1))
					cout << "Bad figure :( \t[" << i << "," << j << "]" << endl;
		}
	}
	for (int i(1); i < r - 1; i++)
	{
		wall = 0;
		//if ((data[i - 1][0] == 1) && (data[i][0] == 1) && (data[i + 1][0] == 1)) wall += 1;
		//if ((data[i - 1][c] == 1) && (data[i][c] == 1) && (data[i + 1][c] == 1)) wall += 1;
		for (int j(1); j < c - 1; j++)
		{			
			if ((data[i - 1][j] == 1) && (data[i][j] == 1) && (data[i + 1][j] == 1)) wall += 1;
			if ((data[i][j - 1] == 1) && (data[i][j] == 1) && (data[i][j - 1] == 1)) wall += 1;
			if ((data[i][j] == 1) && (wall > 2))		
				cout << ":( \t[" << i << "," << j << "]" << endl;
		}
	}
	for (int j(1); j < c - 1; j++)
	{
		wall = 0;
		//if ((data[0][j - 1] == 1) && (data[0][j] == 1) && (data[0][j + 1] == 1)) wall += 1;
		//if ((data[c][j - 1] == 1) && (data[c][j] == 1) && (data[c][j + 1] == 1)) wall += 1;
		for (int i(1); i < r - 1; i++)
		{			
			if ((data[i][j - 1] == 1) && (data[i][j] == 1) && (data[i][j + 1] == 1)) wall += 1;
			if ((data[i - 1][j] == 1) && (data[i][j] == 1) && (data[i + 1][j] == 1)) wall += 1;
			if ((data[i][j] == 1) && (wall > 2))
				cout << "): \t[" << i << "," << j << "]" << endl;
		}
	}
}

void f::Print()
{
	for (int i(0); i < r; i++)
	{
		for (int j(0); j < c; j++)
			cout << data[i][j] << ' ';
		cout << endl;
	}
}

f::~f()
{
}
