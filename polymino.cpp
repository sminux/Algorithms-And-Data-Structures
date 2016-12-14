#include "polymino.h"

polymino::polymino(f *figures, int n)
{
	this->n = n;
	this->figures = new f[n];
	for (int i(0); i < n; i++) this->figures[i] = figures[i];
}



void polymino::poligon()
{
	int globalSquare = 0;
	for (int num(0); num < n; num++)
	{
		cout << endl << "\t#" << num + 1 << endl;
		for (int i(0); i < n; i++) solvation = figures[num].array();
		for (size_t i(0); i < figures[num].get_c(); i++)
		{
			for (size_t j(0); j < figures[num].get_r(); j++)
			{
				cout << solvation[i][j] << " ";
				if (solvation[i][j] == 1) globalSquare += 1;
			}
			cout << endl;
		}
		cout << endl;
	}

	(globalSquare % 2 != 0) ? (cout << "Figures do not add up!") : (cout << "Area of " << globalSquare);

	
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

void polymino::print()
{
	for (int num(0); num < n; num++)
	{
		cout << endl << "\t#" << num + 1 << endl;
		for (int i(0); i < n; i++) solvation = figures[num].array();
		for (size_t i(0); i < figures[num].get_c(); i++)
		{
			for (size_t j(0); j < figures[num].get_r(); j++)
			{
				cout << solvation[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

polymino::~polymino()
{

}