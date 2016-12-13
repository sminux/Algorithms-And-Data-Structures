#include "polymino.h"

polymino::polymino(f *figures, int n)
{
	this->n = n;
	this->figures = new f[n];
	for (int i(0); i < n; i++) this->figures[i] = figures[i];
}

void polymino::print()
{
	for (size_t i(0); i < n-1; i++)
	{
		cout << "||\t#1\t||" << endl;
		figures[i].print();
	}
}

bool polymino::checkSquare(int *arrOfSquares)
{
	bool flag = 0;
	int GlobalSquare = 0;
	for (size_t i(0); i < n; i++) GlobalSquare += 1;
	(GlobalSquare % 2 != 0) ? (flag = false): (flag = true);
	cout << "S" << GlobalSquare << endl;
	return flag;
}


polymino::~polymino()
{

}