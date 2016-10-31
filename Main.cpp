#include "polymino.h"
#include "f.h"

size_t ** read(string s)
{
	ifstream F(s);
	if (!F.is_open())
	{
		cout << "Wrong path to the file!" << endl;
	}
	else
	{
		size_t k = 0, lines = 0;
		queue<size_t> q;
		size_t entr;

		try
		{
			char c;
			while (!F.eof())
			{
				F >> c;
				if (!(isdigit(c)))	//input data is not a int
					throw invalid_argument("\nIncorrect input data! Not a digit!");
			}
			F.close();
			ifstream F(s);

			char *str = new char[1024];
			while (!F.eof())
			{
				F.getline(str, 1024, '\n');
				lines++;
			}

			F.seekg(0, ios::beg);	//cursor to the beginning of file
			F.clear();

			while (!F.eof())
			{
				F >> entr;
				k++;
			}
			if (k > lines*lines)	//if amount of elements more than dimention
				throw invalid_argument("\nIncorrect input data!");
			else
			{
				F.seekg(0, ios::beg);
				F.clear();		//for repeated reading
				k = 0;
				while (!F.eof())
				{
					F >> entr;
					q.push(entr);
					k++;
				}
				size_t N = sqrt((double)k);
				size_t **x = new size_t*[N];
				for (size_t i = 0; i < N; i++) x[i] = new size_t[N];

				for (size_t i = 0; i < N; i++)
				{
					for (size_t j = 0; j < N; j++)
					{
						x[i][j] = q.front();
						cout << x[i][j] << ' ';
						q.pop();
					}
					cout << endl;
				}
				return x;
				for (size_t i = 0; i < N; i++) delete[] x[i];
				delete[] x;
				F.close();
			}
		}
		catch (invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
	}

}
size_t dimention(string s)
{
	ifstream F(s);
	if (!F.is_open())
	{
		cout << "Wrong path to the file!" << endl;
	}
	else
	{
		size_t k = 0;
		size_t entr;
		while (!F.eof())
		{
			F >> entr;
			k++;
		}
		size_t N = sqrt((double)k);
		return N;
	}
}

int main()		
{
	setlocale(LC_ALL, "rus");

	size_t q = 0;
	cout << "Enter the quantity of figures:  ";//each figure in its oun file.txt
	//cin >> q; will be enter a few figures
	q = 1;
	string c;
	for (int quantity = 1; quantity <= q; quantity++)
	{
		c = to_string(quantity);
		string s1 = "D:\\", s2 = ".txt";
		string s = s1 + c + s2;

		cout << endl << "\tFigure #" << quantity << endl;
		f fgr(read(s), dimention(s));
		//fgr.delZeros();
		//if (fgr.checkCorrect()) fgr.print();
		//fgr.rotation90();
		//fgr.print();
		cout << fgr.square() << endl;
		//cout << fgr.findAngle() << endl;

		cout << endl;
	}		

	system("pause");
	return 0;
}
















/*for (int i = 1; i < N / 2; ++i) //turn right
{
int tmp = 0;
for (int k = i; k < N - i; ++k)
{
tmp = x[i][k];
x[i][k] = x[N - k + 1][i];
x[N - k + 1][i] = x[N - i + 1][N - k + 1];
x[N - i + 1][N - k + 1] = x[k][N - i + 1];
x[k][N - i + 1] = tmp;
}
}*/