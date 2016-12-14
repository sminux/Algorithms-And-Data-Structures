#include "polymino.h"

polymino::polymino(f *figures, int n)
{
	cout << "Procces of comparing..." << endl;
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

void polymino::resultFile()
{
	
	ofstream f_res("D:\\HomeWork\\Figures&Result\\result.txt");
	if (!f_res.is_open())
	{
		cout << "Wrong path to the result file!" << endl;
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < colums; j++)
			{
				f_res << solvation[i][j] << ' ';
			}
			f_res << endl;
		}
	}
	f_res.close();
	
}

int polymino::getMaxColumn()
{
	int max_column = 0;
	for (int i(0); i < n; i++)
			if (figures[i].get_c() > max_column) max_column = figures[i].get_c();		
	return max_column;
}

int polymino::getMaxRow()
{
	int max_row = 0;
	for (int i(0); i < n; i++)
		if (figures[i].get_r() > max_row) max_row = figures[i].get_r();
	return max_row;
}

polymino::~polymino()
{

}