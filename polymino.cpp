#include "polymino.h"


polymino::polymino()
{
	size_t q = 2;						//will be enter a few figures, each figure in its own file.txt
	int *square = new int[q];
	f *fgr = new f[q];
	

	polyArr = {0,};
}

bool polymino::checkSquare(int *arrOfSquares, int index)
{
	bool flag = 0;
	int GlobalSquare = 0;
	for (size_t i(0); i < index; i++) GlobalSquare += 1;
	(GlobalSquare % 2 != 0) ? (flag = false): (flag = true);
	return flag;
}

void polymino::compare(f f1, f f2)
{
	int c1 = f1.get_c();
	int c2 = f2.get_c();

}

void polymino::packing()
{
	for (size_t i(0); i < r_glob; i++)
	{
		for (size_t j(0); j < c_glob; j++)
			cout << polyArr[i][j] << ' ';
		cout << endl;
	}
}

void polymino::result()
{
	string namefile;
	for (int quantity = 1; quantity <= q; quantity++)
	{
		namefile = to_string(quantity);
		string s1 = "D:\\HomeWork\\Figures&Result\\", s2 = ".txt";
		string s = s1 + namefile + s2;

		cout << endl << "\tFigure #" << quantity << endl;

		fgr[quantity].read(s);
		cout << fgr[quantity].square() << endl;

		fgr[quantity].delZeros();
		//fgr[quantity].flip();

		fgr[quantity].print();
		square[quantity] = fgr[quantity].square();
		cout << "Square: " << square[quantity] << endl;
	}






	ofstream f_res("D\\result.txt");
	if (!f_res.is_open())
	{
		cout << "Wrong path to the result file!" << endl;
	}
	else
	{
		for (int i = 0; i < r_glob; i++)
		{
			for (int j = 0; j < c_glob; j++)
			{
				f_res << polyArr[i][j] << ' ';
			}
			cout << endl;
		}
	}

	f_res.close();
}
polymino::~polymino()
{
}
