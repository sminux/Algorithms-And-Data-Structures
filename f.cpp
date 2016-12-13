#include "f.h"

f::f()
{
	cout << "in|";		//метка инициализации
	
	size_t **data;
	size_t c = 0, r = 0;
}

int **f::read(string s)
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
			char ch;
			while (!F.eof())
			{
				F >> ch;
				if (!(isdigit(ch)))	//input data is not a int
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
				F.clear();			//for repeated reading
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

				cout << endl;
				for (size_t i = 0; i < N; i++)
				{
					for (size_t j = 0; j < N; j++)
					{
						x[i][j] = q.front();
						//cout << x[i][j] << ' ';
						q.pop();
					}
					//cout << endl;
				}

				data = x;	//go on with data[][]
				c = N;
				r = N;
				cout << "\tInput matr: " << c << " * " << r << endl;		

				//for (size_t i = 0; i < N; i++) delete[] x[i];
				//delete[] x;
				F.close();
			}
		}
		catch (invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
	}
}

int f::square()
{
	int Sq = 0;
	for (size_t i(0); i < r; i++)
	{
		for (size_t j(0); j < c; j++)
		{
			if (data[i][j] == 1) Sq += 1; 
		}
	}
	return Sq;
}

void f::checkCorrect()
{
	bool flag = false;

	const size_t new_A = c * r;	//make new array for adjacency matrix
	size_t **A = new size_t*[new_A];
	for (size_t a = 0; a < new_A; a++) A[a] = new size_t[new_A];
	for (size_t i(0); i < new_A; i++)
			for (size_t j(0); j < new_A; j++) A[i][j] = 0;
	

	for (size_t i(0); i < c-1; i++)
	{
		for (size_t j(0); j < r-1; j++)
		{
			if ((data[i][j] == 1)&&(data[i][j] == data[i][j + 1]))
			{
				A[i][j + 1] = 1;		//matrix is simetric
				A[j + 1][r*i +i] = 1;
			}
		
			if ((data[i][j] == 1) && (data[i][j] == data[i + 1][j]))
			{
				A[i][j + 1] = 1;		//matrix is simetric
				A[j][r*i + 1] = 1;
			}
		}
	}

	for (size_t i(0); i < new_A; i++)
	{
		for (size_t j(0); j < new_A; j++)
		{
			cout << A[i][j] << ' ';
		}
		cout << endl;
	}
	
	
	/*
	int summ_x[(const int)new_A] = {0,};
	for (size_t i(0); i < new_A; i++)	//if string has just one unit -> not normal figure
	{
		for (size_t j(0); j < new_A; j++)
		{
			summ_x[i] =+ A[i][j];
		}
		if (summ_x[i] == 1)
		{
			flag = false;
			break;
		}
	}*/
	
	/*bool **used = new bool*[r];
	for (size_t i = 0; i < r; i++) used[i] = new bool[c];
	used = { 0, };

	for (size_t i(0); i < r-1;)
	{
		for (size_t j(0); j < c - 1;)
		{
			while (data[i][j] != 1) j += 1;

			if ((data[i][j] == 1) && (data[i][j + 1] == 1) && (used[i][j] == 0))
			{
				//проверка является ли это циклом и есть ли отверстия
			}
			else
			{
				used[i][j] = true;
			}
		}
	}
	cout << flag << endl;*/
}

void f::delZeros()	//from square matrix to normal
{
	for (size_t i = 0; i<r; i++)	//delete  empty rows
	{
		int zeros = 0;
		for (size_t j = 0; j < c; j++)
			if (data[i][j] != 0) zeros = 1;
		if (zeros == 0)
		{
			for (size_t y = i; y < r - 1; y++)
				for (size_t j = 0; j<c; j++)
					data[y][j] = data[y + 1][j];
			r--;
			i = 0; 
		}
	}
	
	for (size_t i = 0; i < c; i++)	//delete  empty colums
	{
		int zeros = 0;
		for (size_t j = 0; j < r; j++)
			if (data[j][i] != 0) zeros = 1;
		if (zeros == 0)
		{
			for (size_t y = i; y < c - 1; y++)
				for (size_t j = 0; j<r; j++)
					data[j][y] = data[j][y+1];
			c--;
			i = 0;
		}
	}
	cout << "\tFigure dim: " << c << " * " << r << endl;
}

void f::flip()
{
	for (size_t i = 0; i < r/2; i++)
	{	
		for (size_t j = 0; j < c; j++)
			swap(data[i][j], data[r - i][j]);
	}
}

int f::findAngle()
{
	int s = 0;
	int max = 0;
	for (size_t i = 0; i < r; i++)
	{
		for (size_t j = 0; j < c; j++)
		{
			if (j > 0) s += data[i][j];
			if (i == 0) s += data[i][j];
		}
		if (s >= max)
		{
			max = s;
			s = 0;
		}
		c--; r--;
		findAngle();
	}
	
	return max;
	
}

void f::rotation90L()
{				//P -> P.transponize -> P.flip(horisontaly)
	int x = 0, y = 0;
	for (int j = 0; j < c; j++)
	{
		for (int i = r - 1; i >= 0; i--)
		{
			data[y][x++] = data[i][j];
		} 
		y++; x = 0;
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

int f::get_c()
{
	return c;
}

int f::get_r()
{
	return r;
}

void f::res()
{
	ofstream f_res("D:\\HomeWork\\Figures&Result\\result.txt");
	if (!f_res.is_open())
	{
		cout << "Wrong path to the result file!" << endl;
	}
	else
	{
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < c; j++)
			{
				f_res << data[i][j] << ' ';
			}
			f_res << endl;
		}
	}
	f_res.close();
}

f::~f()
{
}
